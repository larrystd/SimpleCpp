#include <iostream>
class A{
public:
    int a;
    A():a(0x1) {}
    virtual void foo(){ std::cout << "A::foo()" << std::endl; }
    void bar(){ std::cout << "A::bar()" << std::endl; }
};
class B: public A{
public:
    int b;
    B():A(),b(0x2) {}
    void foo(){ std::cout << "B::foo()" << std::endl; }
};
class C: public B{
public:
    int c;
    C():B(), c(0x3) {}
    void foo(){ std::cout << "C::foo()" << std::endl; }
};
int main() {
    A a; B b; C c; B *p = &c;
    p->foo();
    std::cout << sizeof(int) << " " << sizeof(int*) << std::endl;
    return 0;
}