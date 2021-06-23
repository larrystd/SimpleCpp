#pragma once

/*
C++都是通过operator new(std::size_t sz)来申请内存，而这个操作符我们可以重载：

void* operator new(std::size_t size, const char* file, int line);

让底层程序申请内存时调用重载的这个函数, 对new使用宏定义
#define new new (__FILE__, __LINE__)

ANSI C标准中几个标准预定义宏：

__LINE__：在源代码中插入当前源代码行号；
__FILE__：在源文件中插入当前源文件名；
__DATE__：在源文件中插入当前的编译日期；
__TIME__：在源文件中插入当前编译时间；
__STDC__：当要求程序严格遵循ANSI C标准时该标识被赋值为1；
__cplusplus：当编写C++程序时该标识符被定义。

在new A的时候底层就会自动调用operator new(std::size_t size, const char* file, int line)函数

检测内存泄漏关键在于重载new和delete，每分配内存会记录分配内存的信息，终止时检测分配的内存是否均已释放。
*/
#include <stdio.h>

#include <iostream>

void* operator new(std::size_t size, const char* file, int line);
void* operator new[](std::size_t size, const char* file, int line);

void operator delete(void* ptr) noexcept;
void operator delete[](void* ptr) noexcept;

#define new new (__FILE__, __LINE__)            // 实际是三个参数

int checkLeaks();