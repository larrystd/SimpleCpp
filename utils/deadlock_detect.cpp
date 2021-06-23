/*
死锁的四个条件

禁止抢占（no preemption）：系统资源不能被强制从一个进程（线程）中退出，已经获得的资源在未使用完之前不能被抢占。

等待和保持（hold and wait）：一个进程（线程）因请求资源阻塞时，对已获得的资源保持不放。

互斥（mutual exclusion）：资源只能同时分配给一个进程（线程），无法多个进程（线程）共享。

循环等待（circular waiting）：一系列进程（线程）互相持有其他进程（线程）所需要的资源。

只有同时满足以上四个条件，才会产生死锁，想要消除死锁只需要破坏其中任意一个条件即可。

 ps命令查找与进程相关的PID号：
 ps -ef|grep java|grep -v grep 显示出所有的java进程，去处掉当前的grep进程。

 传统gdb调试多线程死锁方法

（1）attach id关联到发生死锁的进程id
（2）info threads查看当前进程中所有线程的信息，也可以查看到部分堆栈信息
多次info threads看看这些线程有没有什么变化，多次如果都没有变化那基本上就是发生了死锁。
（3）thread id进入具体线程

（4）bt查看当前线程堆栈信息

另，在gdb attack线程后，可以执行脚本直接判断有无死锁
死锁检测脚本就是检测的简单环，这里涉及到强连通分量算法和简单环算法
*/
#include <thread>
#include <mutex>
#include <iostream>
using std::cout;

std::mutex mutex1;

std::mutex mutex2;
std::mutex mutex3;

// 持有mutex1, 请求mutex2
void FuncA() {
    std::lock_guard<std::mutex> guard1(mutex1);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::lock_guard<std::mutex> guard2(mutex2);
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

// 持有mutex2,请求mutex3
void FuncB() {
   std::lock_guard<std::mutex> guard2(mutex2);
   std::this_thread::sleep_for(std::chrono::seconds(1));
   std::lock_guard<std::mutex> guard3(mutex3);
   std::this_thread::sleep_for(std::chrono::seconds(1));
}

// 持有mutex3,请求mutex1
void FuncC() {
   std::lock_guard<std::mutex> guard3(mutex3);
   std::this_thread::sleep_for(std::chrono::seconds(1));
   std::lock_guard<std::mutex> guard1(mutex1);
   std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
   std::thread A(FuncA);
   std::thread B(FuncB);
   std::thread C(FuncC);    // 创建完线程就可以执行了

   std::this_thread::sleep_for(std::chrono::seconds(5));

   if (A.joinable()) {
       A.join();
  }
   if (B.joinable()) {
       B.join();
  }
   if (C.joinable()) {
       C.join();
  }
   cout << "hello\n";
   return 0;
}

