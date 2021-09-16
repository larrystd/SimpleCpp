#include <iostream>

using namespace std;

class Base {
public:
    Base() {
        cout << "construct Base"<<endl;
    }
    virtual void f() {
        cout << "Base::f"<<endl;
    }
    virtual void g() {
        cout << "Base::g" <<endl;
    }
    virtual ~Base() {
        cout << "destruct Base" <<endl;
    }
};

class Derive : public Base {
public:
    Derive() {
        cout << "construct Derive"<<endl;
    }
    virtual void f() {
        cout << "derive::f"<<endl;
    }
    virtual void h() {
        cout << "derive::h"<<endl;
    }
    virtual ~Derive() {
        cout << "destruct Base" <<endl;
    }
};

typedef void (*func) ();

int main() {
    Base base;


    
    cout << "vptr虚指针所在地址" << &base <<endl;
    cout << "将地址变为指针类型, 强制转换为了取四个字节, 这时候才是一个虚指针" << (unsigned long *)(&base) <<endl;
    cout << "vptr虚指针解指针, 得到指针指向的内容, 也就是虚表首元素, 指向第一个虚函数的指针" << *(unsigned long *)(&base) <<endl;

    // vbtl是函数指针, 指向虚表第一个元素
    //unsigned long* vtbl = (unsigned long *)(*(unsigned long *)&base);

    unsigned long* vtbl = (unsigned long*)(*(unsigned long*)&base);
    cout << sizeof(vtbl) <<endl;

    cout << "虚表第一个元素(一个函数指针本身,指向虚函数): " << vtbl << endl;
    /// 虚函数本身(函数本身其实是一个指针)
    cout << "虚函数本身: " << *vtbl << endl;
    /// 虚函数本身转为函数类型并调用
    func pfunc = (func)*(vtbl);
    pfunc();


    Base* base_2 = new Derive;

    cout << "vptr虚指针所在地址" << &(*base_2) <<endl;
    cout << "将地址变为指针类型, 强制转换为了取四个字节, 这时候才是一个虚指针" << (unsigned long *)(&(*base_2)) <<endl;
    cout << "vptr虚指针解指针, 得到指针指向的内容, 也就是虚表首元素, 指向第一个虚函数的指针" << *(unsigned long *)(&(*base_2)) <<endl;

    // vbtl是函数指针, 指向虚表第一个元素
    //unsigned long* vtbl = (unsigned long *)(*(unsigned long *)&base);
    
    unsigned long* vtbl_2 = (unsigned long*)(*(unsigned long*)(&(*base_2)));
    cout << sizeof(vtbl_2) <<endl;
    
    cout << "虚表第一个元素(一个函数指针本身,指向虚函数): " << vtbl_2 << endl;
    /// 虚函数本身(函数本身其实是一个指针)
    cout << "虚函数本身: " << *vtbl_2 << endl;
    /// 虚函数本身转为函数类型并调用
    func pfunc_2 = (func)*(vtbl_2);
    pfunc_2();
    
    //delete base;
    return 0;
}