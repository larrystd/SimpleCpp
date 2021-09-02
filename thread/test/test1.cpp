#include <iostream>
#include <thread>

int main() {
    auto f = [] () {
        std::cout << "hello world"<<std::endl;
    };

    // std::thread t(f);

    std::thread *t = new std::thread(f);

    //t->join();
    //t.detach();
    delete t;

    std::cout<< "finish"<<std::endl;
    return 0;

    /// 分离线程可能出现的问题, 线程引用外部变量, 但外部进程已经退出。
    /// 以上同样是lambda表达式可能的问题
}