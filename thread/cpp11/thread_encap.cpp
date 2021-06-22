#include <iostream>
#include <thread>

// 以下的封装可以避免忘记使用detach或者join
class ThreadGuard {
public:
// cpp11引入的类型安全的枚举。枚举类型不能隐式地转换为整数
// 调用时使用ThreadGuard::DesAction::join
    enum class DesAction {join, detach};

    ThreadGuard(std::thread&& t, DesAction a) : t_(std::move(t)), action_(a) {};

    ~ThreadGuard() {
        if (t_.joinable()) {
            if (action_ == DesAction::join) {
                t_.join();
            } else {
                t_.detach();
            }
        }
    }

    ThreadGuard(ThreadGuard& ) = default;
    ThreadGuard& operator= (ThreadGuard&& ) = default;

    std::thread& get() { return t_; }

private:
    std::thread t_;
    DesAction  action_;
};

int main() {
    ThreadGuard t(std::thread([]() {
        for (int i = 0; i < 10; i++){
            std::cout << "thread guard " << i << " ";
        }
        std::cout<<std::endl;
    }), ThreadGuard::DesAction::join);

    return 0;
}