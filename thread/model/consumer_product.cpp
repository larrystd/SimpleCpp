#include <thread>
#include <mutex>
#include <deque>
#include <vector>
#include <condition_variable>

class CThreadDemo
{
private:
	std::deque<int> m_data;
	std::mutex m_mtx; // 全局互斥锁.
	std::condition_variable m_cv; // 全局条件变量.
	int       m_nGen;
 
private:
// 注意生产者消费者是同一把锁
	void ProductThread(){
		while (true){
			std::unique_lock <std::mutex> lck(m_mtx);   
			m_nGen = ++m_nGen % 1000;
			printf("product %d\n", m_nGen);
			m_data.push_back(m_nGen);
			lck.unlock();   // 释放锁
			m_cv.notify_all();  // 唤醒
 
			/* 等待1S */
			std::chrono::milliseconds dura(1000);
			std::this_thread::sleep_for(dura);
		}
	}
 
	void ConsumeThread(){
		while (true){
			std::unique_lock <std::mutex> lck(m_mtx);
			while (m_data.empty()){
				m_cv.wait(lck); // 释放锁并阻塞，等待信号量
			}
			int nData = m_data.front();
			m_data.pop_front();
			printf("consume %d\n", nData);
			lck.unlock();
			
			/* 等待2S */
			std::chrono::milliseconds dura(2000);
			std::this_thread::sleep_for(dura);
		}
	}
public:
	CThreadDemo(){
		m_data.clear();
		m_nGen = 0;
	}
 
	void Start(){
		std::vector<std::thread> threads;
		threads.clear();
		for (int i = 0; i < 5; i++){/* 生产者线程 */
			threads.push_back(std::thread(&CThreadDemo::ProductThread, this));
		}
		for (int i = 5; i < 10; i++){/* 消费者线程 */
			threads.push_back(std::thread(&CThreadDemo::ConsumeThread, this));
		}
		for (auto& t : threads){/* 等待所有线程的退出 */
			t.join();
		}
	}
};
 
 
int main()
{
	CThreadDemo test;
	test.Start();
	return 0;
}