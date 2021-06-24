#ifndef __TIMER__
#define __TIMER__

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>

#include "map.h"
#include "include/thread_pool.h"

/*
一个完备的定时器需要有如下功能：

在某一时间点执行某一任务
在某段时间后执行某一任务
重复执行某一任务N次，任务间隔时间T

优先级任务队列：队列中存储任务，每个任务会添加时间戳，最近的时间戳的任务会先出队。
锁和条件变量：当有任务需要执行时，用于通知正在等待的线程从任务队列中取出任务执行。
线程池：当时间到了，优先级队列中的任务会出队在线程池中执行。
*/

namespace kvr {
class TimerQueue {
   public:
    struct InternalS {
        std::chrono::time_point<std::chrono::high_resolution_clock> time_point_;
        std::function<void()> func_;
        int repeated_id;
        bool operator<(const InternalS& b) const { return time_point_ > b.time_point_; }
    };

   public:
   // 打开内部的线程池功能，用于执行放入定时器中的任务，同时新开一个线程，循环等待任务到来后送入线程池中执行。
    bool Run() {
        bool ret = thread_pool_.Start();
        if (!ret) {
            return false;
        }
        std::thread([this]() { RunLocal(); }).detach();
        return true;
    }

    bool IsAvailable() { return thread_pool_.IsAvailable(); }

    int Size() { return queue_.size(); }

    // 关闭定时器
    // 标志位为false，调度线程的循环就会自动退出，就不会继续等待任务执行。
    void Stop() {
        running_.store(false);
        cond_.notify_all();
        thread_pool_.ShutDown();
    }

    template <typename R, typename P, typename F, typename... Args>
    void AddFuncAfterDuration(const std::chrono::duration<R, P>& time, F&& f, Args&&... args) {
        InternalS s;
        s.time_point_ = std::chrono::high_resolution_clock::now() + time;
        s.func_ = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(s);
        cond_.notify_all();
    }

    // 根据时间戳构造InternalS，放入队列中
    template <typename F, typename... Args>
    void AddFuncAtTimePoint(const std::chrono::time_point<std::chrono::high_resolution_clock>& time_point, F&& f,
                            Args&&... args) {
        InternalS s;
        s.time_point_ = time_point;
        s.func_ = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(s);
        cond_.notify_all();
    }

    template <typename R, typename P, typename F, typename... Args>
    int AddRepeatedFunc(int repeat_num, const std::chrono::duration<R, P>& time, F&& f, Args&&... args) {
        int id = GetNextRepeatedFuncId();
        repeated_id_state_map_.Emplace(id, RepeatedIdState::kRunning);
        auto tem_func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        AddRepeatedFuncLocal(repeat_num - 1, time, id, std::move(tem_func));
        return id;
    }

    void CancelRepeatedFuncId(int func_id) { repeated_id_state_map_.EraseKey(func_id); }

    int GetNextRepeatedFuncId() { return repeated_func_id_++; }

    TimerQueue() : thread_pool_(kvr::ThreadPool::ThreadPoolConfig{4, 4, 40, std::chrono::seconds(4)}) {
        repeated_func_id_.store(0);
        running_.store(true);
    }

    ~TimerQueue() { Stop(); }

    enum class RepeatedIdState { kInit = 0, kRunning = 1, kStop = 2 };

   private:
   // 循环等待任务到来后送入线程池中执行。
    void RunLocal() {
        while (running_.load()) {
            std::unique_lock<std::mutex> lock(mutex_);
            if (queue_.empty()) {
                cond_.wait(lock);   // 等待任务
                continue;
            }
            auto s = queue_.top();
            auto diff = s.time_point_ - std::chrono::high_resolution_clock::now();  // 时间戳到当前的时间差
            if (std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() > 0) {
                cond_.wait_for(lock, diff); // 等待之
                continue;
            } else {
                queue_.pop();
                lock.unlock();
                thread_pool_.Run(std::move(s.func_));
            }
        }
    }

    template <typename R, typename P, typename F>
    void AddRepeatedFuncLocal(int repeat_num, const std::chrono::duration<R, P>& time, int id, F&& f) {
        if (!this->repeated_id_state_map_.IsKeyExist(id)) {
            return;
        }
        InternalS s;
        s.time_point_ = std::chrono::high_resolution_clock::now() + time;
        auto tem_func = std::move(f);
        s.repeated_id = id;
        s.func_ = [this, &tem_func, repeat_num, time, id]() {
            tem_func();
            if (!this->repeated_id_state_map_.IsKeyExist(id) || repeat_num == 0) {
                return;
            }
            AddRepeatedFuncLocal(repeat_num - 1, time, id, std::move(tem_func));
        };
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(s);
        lock.unlock();
        cond_.notify_all();
    }

   private:
   // 优先队列
    std::priority_queue<InternalS> queue_;
    std::atomic<bool> running_;
    std::mutex mutex_;
    std::condition_variable cond_;

    kvr::ThreadPool thread_pool_;

    std::atomic<int> repeated_func_id_;
    kvr::ThreadSafeMap<int, RepeatedIdState> repeated_id_state_map_;
};

}  // namespace

#endif