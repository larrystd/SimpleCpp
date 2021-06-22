/*
异步操作，主要是std::future std::promise和std::packaged_task

std::future可以认为是传输通道，使用get()可以获得线程函数的返回值。
std::promise包装一个值，并与std::future绑定。
std::packaged_task包装一个调用对象，与future绑定。

future用来获取数据
*/

#include <functional>
#include <future>
#include <iostream>
#include <thread>

using namespace std;

void func (std::future<int>& fut) {
    int x = fut.get();
    cout << "value: " << x <<endl;
}

int func1(int in) {
    return in+1;
}

int main() {
    std::promise<int> prom; // 封装数据
    std::future<int> fut = prom.get_future();
    std::thread t(func, std::ref(fut));
    prom.set_value(144);
    t.join();

    std::packaged_task<int(int)> task(func1);
    std::future<int> fut1 = task.get_future();
    std::thread(std::move(task), 5).detach();
    cout << "result " << fut1.get() <<endl;
    return 0;
}