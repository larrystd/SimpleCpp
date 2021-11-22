#include <iostream>       // std::cout
#include <atomic>         // std::atomic
#include <thread>         // std::thread
#include <vector>         // std::vector

std::atomic<bool> ready (false);
std::atomic<bool> winner (false);

void count1m (int id) {
  while (!ready) {}    // 等待开始, ready也是原子的 
  for (int i=0; i<1000000; ++i) {}  
  if (!winner.exchange(true)) // winner赋新值为true,返回赋值前的值false
   { std::cout << "thread #" << id << " won!\n"; }
};

class A {
public:
  int a_;
  static std::atomic<int> b_;
};

std::atomic<int> A::b_;


void* thread_exec (void* arg) {
  std::cout << A::b_ <<"\n";

  return 0;
}

int main ()
{
  /*
  std::vector<std::thread> threads;
  std::cout << "spawning 10 threads that count to 1 million...\n";
  for (int i=1; i<=10; ++i) threads.push_back(std::thread(count1m,i));
  ready = true;
  for (auto& th : threads) th.join();
  */


 //std::cout << sizeof(b) <<"\n";
 A::b_ = 1;
  std::cout << A::b_ <<"\n";
 //std::thread th = std::thread(thread_exec);
 pthread_t sp;
 pthread_create(&sp, NULL, thread_exec, NULL);
 void* status;
  pthread_join(sp, &status);
  return 0;
}