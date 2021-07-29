#include <thread>
#include <mutex>
#include <queue>
#include <deque>
#include <condition_variable>

class ConsumerDemo {
private:
	std::deque<int> shared_data;
	std::mutex mtx_;	// 锁
	std::condition_variable cv_;	// 条件变量
	int		num_;

private:
	void productThread() {
		while (true) {
			std::unique_lock<std::mutex> lck(mtx_);
			num_ = ++num_ % 100;
			printf("product %d\n", num_);
			shared_data.push_back(num_);
			lck.unlock();	// 释放锁


			/* 等待1S */
			std::chrono::milliseconds dura(1000);
			std::this_thread::sleep_for(dura);
		}
	}

	void consumeThread() {
		while (true) {
			std::unique_lock<std::mutex> lck(mtx_);
			while (shared_data.empty()) {
				cv_.wait(lck);	// wait unique_lock 而不是mutex
			}
			int n_data = shared_data.front();
			shared_data.pop_front();
			printf("consume %d\n", n_data);
			lck.unlock();


			/* 等待2S */
			std::chrono::milliseconds dura(2000);
			std::this_thread::sleep_for(dura);
		}
	}

public:
	ConsumerDemo() {
		shared_data.clear();
		num_ = 0;
	}

	void start() {
		std::vector<std::thread> threads;
		for (int i = 0; i < 3; i++){
			// 传参数为this
			// 一旦调用std::thread()构造实例，线程将立即执行
			threads.push_back(std::thread(&ConsumerDemo::productThread, this));
		}
		for (int i = 3; i < 6; i++){
			threads.push_back(std::thread(&ConsumerDemo::consumeThread, this));
		}
		for (auto& t : threads){
			// 阻塞等待线程执行完毕
			t.join();
		}
	}
};

int main() {
	ConsumerDemo demo;
	demo.start();


	return 0;
}
