#ifndef __DEFER__
#define __DEFER__

#include "noncopyable.h"

#include <functional>
#include <iostream>

// reference https://github.com/loveyacper/ananas

namespace kvr {

class ExecuteOnScopeExit : NonCopyAble {
   public:
    ExecuteOnScopeExit() = default;

    ExecuteOnScopeExit(ExecuteOnScopeExit&&) = default;
    ExecuteOnScopeExit& operator=(ExecuteOnScopeExit&&) = default;

    template <typename F, typename... Args>
    ExecuteOnScopeExit(F&& f, Args&&... args) {
        func_ = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    }

    ~ExecuteOnScopeExit() noexcept {
        if (func_) {
            func_();
        }
    }

   private:
    std::function<void()> func_;
};

}  // namespace kvr

#define _CONCAT(a, b) a##b
#define _MAKE_DEFER_(line) kvr::ExecuteOnScopeExit _CONCAT(defer, line) = [&]()

#undef WZQ_DEFER
#define WZQ_DEFER _MAKE_DEFER_(__LINE__)

#endif