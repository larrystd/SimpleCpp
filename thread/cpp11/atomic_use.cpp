#include <atomic>

struct Counter {
    std::atomic<int> count;

    void add() {
        ++count;
        // 或count.store(++count)
    }

    int get() {
        return count.load();
    }
};