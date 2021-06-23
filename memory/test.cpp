/*
如果程序中存在内存泄漏，我们的目的是找到这些内存是在哪里分配的，如果能够具体对应到代码中哪一个文件的那一行代码最好。

整体思路
在申请内存时记录下该内存的地址和在代码中申请内存的位置，在内存销毁时删除该地址对应的记录，
程序最后统计下还有哪条记录没有被删除，如果还有没被删除的记录就代表有内存泄漏。
*/

#include <iostream>
#include <memory>
#include <mutex>

#include "MemoryDetect.h"

struct A {
    int a;
};

int main() {
    printf("memory detect \n");
    int *p1 = new int;
    delete p1;

    int *p2 = new int[4];
    delete[] p2;

    A *a1 = new A;
    // delete a1;

    A *a2 = new A[1];
    delete[] a2;

    { std::shared_ptr<A> a = std::make_shared<A>(); }
    checkLeaks();
    return 0;
}