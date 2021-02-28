#include <iostream>
using namespace std;

class Base   
{  
public:  
    virtual ~Base() {}  
};  
class Derived : public Base {};  
int main()  
{  
    Derived d;  
    Base& b = d;  
    cout << typeid(b).name() << endl;  
    return 0;
} 