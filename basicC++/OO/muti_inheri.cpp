
#include<iostream>
using namespace std;

class D{
public:
    D(){cout<<"D Constructor\n";}
    ~D(){cout<<"D Destructor\n";}
};

class C : public virtual D{
    public:
        C(){cout<<"C Constructor\n";}
        ~C(){cout<<"C Destructor\n";}
};
 
class B : public virtual D{
    public:
        B(){cout<<"B Constructor\n";}
        ~B(){cout<<"B Destructor\n";}
 
};
 
class A:public C,public B
{
    public:
        A(){cout<<"A Constructor\n";}
        ~A(){cout<<"A Destructor\n";}
 
};
 
int main(){
    A a;
    return 0;
}