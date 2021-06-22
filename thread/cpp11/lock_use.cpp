/*
cpp11 两种RAII的锁封装
std::lock_guard和std::unique_lock
std::lock_guard相比更加轻量级，少一些成员函数。
std::unique_lock有unlock函数，可以手动释放锁。因此条件变量需要配合std::unique_lock使用
*/

#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

std::mutex mutex_;

int main() {
    auto func1 = [](int k) {
        std::unique_lock<std::mutex> lock(mutex_);

        for (int i = 0; i < k; i++) {
            cout << i << " ";
        }
        cout << endl;
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