#ifndef COUNT_DOWN_LATCH_
#define COUNT_DOWN_LATCH_

#include "noncopyable.h"

#include <condition_variable>
#include <iostream>
#include <mutex>

namespace kvr {
class CountDownLatch : NonCopyAble {
   public:
    explicit CountDownLatch(uint32_t count);

    void CountDown();

    void Await(uint32_t time_ms = 0);

    uint32_t GetCount() const;

   private:
    std::condition_variable cv_;
    mutable std::mutex mutex_;
    uint32_t count_ = 0;
};
}  // namespace kvr

#endif