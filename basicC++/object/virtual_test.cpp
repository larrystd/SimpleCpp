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

int main() {
    Base* base = new Derive();
    base->f();

    cout << base->vptr<<endl;
    delete base;
    return 0;
}