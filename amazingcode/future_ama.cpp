/*
cpp 11中的future，达到阻塞线程的目的。
*/

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class GLTaskDispatch {
public:
    static GLTaskDispatch &getInstance() {
        static GLTaskDispatch t;
        return t;
    }

    bool start() {
        auto func = [this]() {
            while (! _interrupt.load()) {       // _interrupt == false
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->_taskMutex);
                    this->_taskCv.wait(lock, [this] {
                        return this->_interrupt.load() || !this->_tasks.empty();
                    });
                    // 只有当 pred 条件为 false 时调用 wait() 才会阻塞当前线程，并且在收到其他线程的通知后只有当 pred 为 true 时才会被解除阻塞
                    // 显然当_interrupt==fasle且_tasks为空时会阻塞。
                    // 唤醒时必须notify和pred同时作用
                    if (this->_interrupt.load()) {
                        continue;
                    }
                    task = std::move(this->_tasks.front());
                    // 获取task
                    this->_tasks.pop();
                }
                task(); // 执行task()
            }
        };
        // Constructs an object of type T and wraps it in a std::unique_ptr.
        // std::make_unique起到构造对象的作用
        _thread = std::make_unique<std::thread>(func);
        return true;
    }

    bool stop() {
        _interrupt.store(true);
        this->_taskCv.notify_all();
        if (_thread && _thread->joinable()) {
            _thread->join();
        }
        return true;
    }

    template <typename F, typename... Args>
    auto run(F&& f, Args&&... args)
        -> std::shared_ptr<std::future<std::result_of_t<F(Args...)>>>
    {
        using returnType = std::result_of_t<F(Args...)>;    // 推断返回值类型
        // 封装task，packaged_task
        auto task = std::make_shared<std::packaged_task<returnType()>>( // 将函数对象封装到packaged_task中
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)  // 封装函数
        );

        std::future<returnType> ret = task->get_future();
        // task对象入队列
        {
            std::lock_guard<std::mutex> lock(this->_taskMutex);
            this->_tasks.emplace([task]() {
                (*task)();  // std::function<void()>
            });
        }

        this->_taskCv.notify_all(); // 唤醒start的阻塞
        // return 一个future对象，可以get异步执行的数据
        return std::make_shared<std::future<std::result_of_t<F(Args...)>>>(std::move(ret) );
    }

private:
    GLTaskDispatch() {} // 不能调用构造函数，但不是单例

    std::unique_ptr<std::thread> _thread = nullptr; 
    std::atomic<bool> _interrupt{false};
    std::queue<std::function<void()>> _tasks;   // 函数队列
    std::mutex _taskMutex;
    std::condition_variable _taskCv;
};

void func1() {
    for (int i = 0; i < 20; i++) {
        std::cout<< "func1 "<< i << "\n";
    }
}

int func2() {
    for (int i = 0; i < 20; i++) {
        std::cout << "func2"<< i << "\n";
    }
    return 39;
}

int main() {
    GLTaskDispatch &t = GLTaskDispatch::getInstance();
    t.start();  // 等待
    t.run(func1)->get();    // 这里通过返回的future,实现了异步阻塞线程的效果。main线程必须等待t执行完毕获取到结果后才可以继续向下执行
    std::cout << "func1 return \n";
    int d = t.run(func2)->get();
    std::cout << "return " << d << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    t.stop();
    return 0;
}