#include <memory>
#include <iostream>
#include <functional>

using namespace std;

struct A {
   explicit A(int value) { // 没有explicit关键字
       cout << "value" << endl;
  }
};

int main() {
   A a(1.2); // 可以隐式转换
   return 0;
}