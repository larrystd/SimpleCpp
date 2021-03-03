# include <iostream>
using namespace std;

class Base{
public:
	virtual void fun(){
        cout<< "Base fun()"<<endl;
    } 
};
class Derived : public Base{
public:
	int i;
    virtual void fun(){
        cout<< "Derived fun()"<<endl;
    } 
 };

int main(){
    Base *Bptr = new Base();//语句0
    Base *Dptr1 = new Derived();//语句0
    Derived *Dptr2 = new Derived();
 
    cout << typeid(Dptr1).name() <<" "<< typeid(Bptr).name() <<endl;
    cout << (typeid(*Dptr1) == typeid(*Dptr2)) <<endl;

    Derived *Dptr_1 = static_cast<Derived *>(Dptr1); //语句1；
    Derived *Dptr_2 = dynamic_cast<Derived *>(Dptr1); //语句2；
    Dptr1->fun();
    Dptr2->fun();
    return 0;
}
