#include <iostream>
#include <thread>

using namespace std;

int main() {
    auto func1 = []() {
        for (int i = 0; i < 10; i++) {
            cout << i << " ";
        }
        cout << endl;
    };

    std::thread t(func1);
    if (t.joinable()) {
        t.detach(); // 线程被os托管，主线程执行完该线程可能没有执行。
    }

    auto func2 = [](int k) {
        for (int i = 0; i < k; i++) {
            cout << i << " ";
        }
        cout << endl;
    };
    std::thread tt(func2, 20);
    if (tt.joinable()) {
        tt.join(); // 会阻塞主线程，
    }


    std::thread ttt(func1);
    cout << "当前线程ID " << t.get_id() <<endl;
    cout << "当前cpu个数" << std::thread::hardware_concurrency() <<endl;

    auto handle = t.native_handle();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}