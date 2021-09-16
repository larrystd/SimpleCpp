#include <iostream>
using namespace std;
 
class Base
{
public :
    int base_data;
    Base() { base_data = 1; }
    virtual void func1() { cout << "base_func1" << endl; }
    virtual void func2() { cout << "base_func2" << endl; }
    virtual void func3() { cout << "base_func3" << endl; }
};
 
class Derive : public Base
{
public :
    int derive_data;
    Derive() { derive_data = 2; }
    virtual void func1() { cout << "derive_func1" << endl; }
    virtual void func2() { cout << "derive_func2" << endl; }
};
 

/// 声明一个函数指针类型
typedef void (*func)();
 
int main()
{
    Base base;
    Base base2;
    Base* base3 = new Derive;

    cout << "&base: " << &base << endl;
    cout << "&base2 对象地址: " << &base2 << endl;
    cout << "&base.base_data: " << &base.base_data << endl;
    cout << "----------------------------------------" << endl;
 
    Derive derive;
    cout << "&derive: " << &derive << endl;
    cout << "&derive.base_data: " << &derive.base_data << endl;
    cout << "&derive.derive_data: " << &derive.derive_data << endl;
    cout << "----------------------------------------" << endl;
 
    for(int i=0; i<3; i++)
    {
        // &base : base首地址
        // (unsigned long*)&base : base的首地址，vptr的地址。 强制转型为long 指针
        // (*(unsigned long*)&base) : vptr的内容(解地址, 指向的内容)，即vtable的地址，指向第一个虚函数的slot的地址
        // (unsigned long*)(*(unsigned long*)&base) : 指向的内容还是一个地址, 即vtable的地址，指向第一个虚函数的slot的地址
        // vtbl : 指向虚函数slot的地址
        // *vtbl : 虚函数的地址
        unsigned long* vtbl = (unsigned long*)(*(unsigned long*)&base) + i;
        cout << "slot address: " << vtbl << endl;
        cout << "func address: " << *vtbl << endl;
        /// 转化成函数类型
        func pfunc = (func)*(vtbl);
        pfunc();
    }
    cout << "----------------------------------------" << endl;
 
    for(int i=0; i<3; i++)
    {
        unsigned long* vtbl = (unsigned long*)(*(unsigned long*)&base2) + i;
        cout << "虚函数表slot address: " << vtbl << endl;
        cout << "func address: " << *vtbl << endl;
        func pfunc = (func)*(vtbl);
        pfunc();
    }
    cout << "----------------------------------------" << endl;

    for(int i=0; i<3; i++)
    {
        unsigned long* vtbl = (unsigned long*)(*(unsigned long*)&derive) + i;
        cout << "derive 虚函数表slot address: " << vtbl << endl;
        cout << "func address: " << *vtbl << endl;
        func pfunc = (func)*(vtbl);
        pfunc();
    }
    cout << "----------------------------------------" << endl;


    for(int i=0; i<3; i++)
    {
        unsigned long* vtbl = (unsigned long*)(*(unsigned long*)&(*base3)) + i;
        cout << "虚函数表slot address: " << vtbl << endl;
        cout << "func address: " << *vtbl << endl;
        func pfunc = (func)*(vtbl);
        pfunc();
    }
    cout << "----------------------------------------" << endl;
    return 1;
}