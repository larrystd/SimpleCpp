/*
std::mutex是一种线程同步的手段，分为四种
std::mutex 独占的互斥量，不可重入，无超时功能
std::recursive_mutex 可重入互斥量，无超时功能
std::timed_mutex 带超时的互斥量，不可重入
std::recursive_timed_mutex, 可重入，带超时功能互斥量。

time_mutex相比于mutex可多一个参数，std::chrono::milliseconds(10) 计时
*/

#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
std::mutex mutex_;

int main() {
    auto func1 = [](int k) {
        mutex_.lock();
        for (int i = 0; i < k; ++i) {
            cout << i << " ";
        }
        cout << endl;
        mutex_.unlock();
    };
    std::thread threads[5];
    for (int i = 0; i < 5; i++) {
        threads[i] = std::thread(func1, 20);
    }
    for (auto& th : threads) {
        th.join();  // 执行，并阻塞main线程
    }
    return 0;
}