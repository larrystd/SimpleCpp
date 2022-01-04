#include <iostream>
#include <thread>
#include <condition_variable>
#include <queue>
#include <mutex>
#include <vector>

class consumerDemo {

    consumerDemo() {
        num_ = 0;
    }

    void start() {
        std::vector<std::thread> threads;
		for (int i = 0; i < 3; i++){
			// 传参数为this
			// 一旦调用std::thread()构造实例，线程将立即执行
			threads.push_back(std::thread(&consumerDemo::productThread, this));
		}
		for (int i = 3; i < 6; i++){
			threads.push_back(std::thread(&consumerDemo::consumeThread, this));
		}
		for (auto& t : threads){
			// 阻塞等待线程执行完毕
			t.join();
		}
    }

    void productThread() {
        while (true) {
            std::unique_lock<std::mutex> lck(mtx_);
            num_ = ++num_ % 100;
            printf("product %d\n", num_);
			shared_queue_.push(num_);
			lck.unlock();	// 释放锁


            /* 等待1S */
			std::chrono::milliseconds dura(1000);
			std::this_thread::sleep_for(dura);
        }
    }

	void consumeThread() {
		while (true) {
			std::unique_lock<std::mutex> lck(mtx_);
			while (shared_queue_.empty()) {
				cv_.wait(lck);	// wait unique_lock 而不是mutex
			}
			int n_data = shared_queue_.front();
			shared_queue_.pop();
			printf("consume %d\n", n_data);
			lck.unlock();


			/* 等待2S */
            std::chrono::milliseconds dura(1000);
			std::this_thread::sleep_for(dura);
		}
	}

private:
    mutable std::mutex mtx_;
    std::condition_variable cv_;
    std::queue<int> shared_queue_;
    int num_;
};
