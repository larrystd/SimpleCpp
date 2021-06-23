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
            while (! _iterrupt)
        }
    }
private:
    GLTaskDispatch() {}
    std::unique_ptr<std::thread> _thread = nullptr;
    std::atomic<bool> _interrupt{false};
    std::queue<std::function<void()>> _tasks;
    std::mutex _taskMutex;
    std::condition_variable _taskCv;
}