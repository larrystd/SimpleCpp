#include<iostream>  
#include <typeinfo>  
using namespace std;  

class Base{};
class Derived:public Base{};
void func1();
int func2(int n);

int main()  
{  
    int a = 10;
    int* b = &a;
    float c;
    double d;

    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;
    cout << typeid(c).name() << endl;
    cout << typeid(d).name() << endl;
    cout << typeid(Base).name() << endl;
    cout << typeid(Derived).name() << endl;
    cout << typeid(func1).name() << endl;
    cout << typeid(func2).name() << endl;

    return 0;
}  