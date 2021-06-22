/*
async是基于任务的异步操作，返回的结果保存在future中

async(std::launch::async | std::launch::deferred, func, args...);
std::launch::async 表示任务执行在另一个线程

std::launch::deferred 表示延迟执行任务
*/

#include <functional>
#include <future>
#include <iostream>
#include <thread>

using namespace std;

int func (int in) { return in + 1; }

int main() {
    auto res = std::async(func, 5);

    cout << res.get() <<endl;
    return 0;
}