#include <iostream>
#include <thread>

#include "include/noncopyable.h"
#include "timer.h"

void TestTimerQueue() {
    kvr::TimerQueue q;
    q.Run();
    for (int i = 5; i < 15; ++i) {
        q.AddFuncAfterDuration(std::chrono::seconds(i + 1), [i]() { std::cout << "this is " << i << std::endl; });

        q.AddFuncAtTimePoint(std::chrono::high_resolution_clock::now() + std::chrono::seconds(1),
                             [i]() { std::cout << "this is " << i << " at " << std::endl; });
    }

    int id = q.AddRepeatedFunc(10, std::chrono::seconds(1), []() { std::cout << "func " << std::endl; });
    std::this_thread::sleep_for(std::chrono::seconds(4));
    q.CancelRepeatedFuncId(id);

    std::this_thread::sleep_for(std::chrono::seconds(30));
    q.Stop();
}

int main() {
    TestTimerQueue();
    return 0;
}