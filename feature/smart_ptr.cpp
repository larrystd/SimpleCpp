/*
cpp11引入了三种智能指针
位于#include <memory>
std::shared_ptr
std::weak_ptr
std::unique_ptr

shared_ptr使用引用计数，每次拷贝触发引用+1，每次生命周期结束析构引用计数-1。
最后一个shared_ptr析构的时候，内存才会释放

智能指针可以自定义删除器，当引用计数为0时自动调用删除器来释放对象的内存
std::shared_ptr<int> ptr(new int, [](int* p) { delete p;})

尽量使用make_shared，少用new
避免循环引用


weak_ptr用来监视shared_ptr的声明周期，可以认为是一个旁观者监视shared_ptr的资源是否存在
同时也可以解决循环引用问题

unique_ptr是一个独占型智能指针，使用方法与shared_ptr类似，区别是不可拷贝
*/
#include <iostream>
#include <memory>

using namespace std;

struct ClassWraper {
    ClassWraper() {
        cout << "construct" <<endl;
        data = new int[10];
    }
    ~ClassWraper() {
        cout << "deconstruct" <<endl;
        if (data != nullptr) {
            delete[] data;
        }
    }
    void Print () {
        cout << "print "<<endl;
    }
    int* data;
};

void Func(std::shared_ptr<ClassWraper> ptr) {
    ptr->Print();
}


struct A;
struct B;

struct A {
    std::shared_ptr<B> bptr;
    ~A() {
        cout << "A delete" <<endl;
    }
    void Print() {
        cout << "A" <<endl;
    }
};

struct B {
    std::weak_ptr<A> aptr;  // 如果是shared_ptr可能循环引用，也就是 A->B B->A
    ~B() {
        cout << "B delete" <<endl;
    }
    void PrintA() {
        if (!aptr.expired()) {  // true if the managed object has already been deleted, false otherwise.
            auto ptr = aptr.lock();
            ptr-> Print();
        }
    }
};

int main() {
    auto smart_ptr = std::make_shared<ClassWraper>();
    auto ptr2 = smart_ptr;
    ptr2->Print();
    Func(smart_ptr);    // 引用计数会+1
    smart_ptr->Print();
    ClassWraper* p = smart_ptr.get();
    p->Print();


    auto aaptr = std::make_shared<A>();
    auto bbptr = std::make_shared<B>();
    aaptr->bptr = bbptr;
    bbptr->aptr = aaptr;
    bbptr->PrintA();
    // 这时候A,B均会被析构
    return 0;
}