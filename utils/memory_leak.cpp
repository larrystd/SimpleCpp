/*
内存泄漏是指由于疏忽或错误造成程序未能释放已经不再使用的内存。

工具
AddressSanitizer(ASan)，该工具为gcc自带，4.8以上版本都可以使用，支持Linux、OS、Android等多种平台，不止可以检测内存泄漏，它其实是一个内存错误检测工具，可以检测的问题有：

内存泄漏
堆栈和全局内存越界访问
free后继续使用
局部内存被外层使用
Initialization order bugs

https://github.com/google/sanitizers/wiki/AddressSanitizer

C++中数组长度可以是变量，但是不建议使用，因为数组使用的是栈内存，变量可以是个比较大的数，这样会导致stack overflow，建议使用堆内存。

操作超过数组长度的内存可以编译通过且表面上看不出来问题，但是会导致栈内存出现脏写，最终可能会引发难以排查的bug，建议数组使用std::array，操作超过长度的下标会抛异常有利于开发者及时发现错误
*/

// 检测内存泄漏
#include <stdlib.h>

void func1() { malloc(7); }

void func2() { malloc(5); }

int main() {
   func1();
   func2();
   return 0;
}

/*
编译输出
g++ -fsanitize=address -g test_leak.cc && ./a.out
只需要添加-fsanitize=address -g就可以检测出具体产生内存泄漏的位置以及泄漏空间的大小。
*/
// 检测堆栈内存越界访问
int main() {
   int *array = new int[100];
   array[0] = 0;
   int res = array[100];  // out of bounds
   delete[] array;
   return res;
}

//free后被使用
int main() {
    int *array = new int[100];
    delete[] array;
    int a = array[0];  // error
    return 0;
}