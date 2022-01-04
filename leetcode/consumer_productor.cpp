#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>


using namespace std;

class ComsumerDemo {
public:
    void comsumer() {
        while (true) {
            //std::lock_guard<std::mutex> lcg(mtx);
            {
                std::unique_lock<std::mutex> lck(mtx);
                //ctx.wait(lck, [this]() {
                //    return !q.empty();
                //});

                while (q.empty()) {
                    ctx.wait(lck);	// wait unique_lock 而不是mutex
                }
                int data = q.front();
                q.pop();
                printf("consume %d\n", data);
                cout << "consume q.size="<< q.size() <<endl;
                lck.unlock();
            }

            ctx.notify_all();
            /* 等待2S */

            // 一定留足时间
			std::chrono::milliseconds dura(2000);
			std::this_thread::sleep_for(dura);
        }      
    }

    void productor() {
        while (true) {

            std::unique_lock<std::mutex> lck(mtx);
            num = (num+1)%10;
            int n = q.size();
            //ctx.wait(lck, [this, n]() {
            //    cout << "q.size="<< n <<endl;
            //    return n < 10;
            //});

            while (q.size() >= 10) {
                ctx.wait(lck);
            }
            q.push(num);
            printf("produce %d\n", num);
            lck.unlock();
            ctx.notify_all();

                        /* 等待1S */
			std::chrono::milliseconds dura(1000);
			std::this_thread::sleep_for(dura);
        }
    }

    void start() {
        // 创建后自动执行函数
        std::thread t1(&ComsumerDemo::comsumer, this);
        std::thread t2(&ComsumerDemo::productor, this);
        //std::thread t3(&ComsumerDemo::comsumer, this);

        t1.join();
        t2.join();
        //t3.join();
    }
private:
    std::mutex mtx;
    std::condition_variable ctx;
    queue<int> q;
    int num;
};

int main () {
    ComsumerDemo comsumerdemo;
    comsumerdemo.start();

    return 0;
}