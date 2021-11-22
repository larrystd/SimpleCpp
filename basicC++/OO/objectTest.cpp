#include <iostream>
using namespace std;


class Base{
public:
    Base(){
        a = 1;
        cout << "constructor Base" <<endl;
    };
    ~Base(){
        cout << "destructor Base" <<endl;
    };

    int a;
};

class Derive : public Base{
public:
    Derive(){
        cout << "constructor Derive" <<endl;
    };
    ~Derive(){
        cout << "destructor Derive" <<endl;
    };

    void print() {
        cout << a<<endl;
        cout << Base::a<<endl;
        cout << Derive::a<<endl;
        cout << Derive::Base::a<<endl;
    }

    int a;
};


int main(){
    //Base *p = new Derive[2];
    //delete[] p;
    Derive derive;
    derive.print();

    // Derive *d = new Derive;
    // delete d;
    // Derive d;
    return 0;
}