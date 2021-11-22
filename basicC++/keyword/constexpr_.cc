#include <memory>
#include <iostream>
#include <functional>

using namespace std;

constexpr int func(int i) {
   return i + 1;
}

int main() {
   int i = 2;
   func(i);// 普通函数
   func(2);// 编译期间就会被计算出来

   constexpr int a = 3;
   int aa = static_cast<int> (a);
   cout << ++aa<<endl;

   const int constant = 21;
    const int* const_p = &constant;
    int* modifier = const_cast<int*>(const_p);
    *modifier = 7;
}