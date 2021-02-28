#include <iostream>
using namespace std;


class Base{
public:
    Base(){
        cout << "constructor Base" <<endl;
    };
    virtual ~Base(){
        cout << "destructor Base" <<endl;
    };
};

class Derive : public Base{
public:
    Derive(){
        cout << "constructor Derive" <<endl;
    };
    ~Derive(){
        cout << "destructor Derive" <<endl;
    };
};


int main(){
    Base *p = new Derive[2];
    delete[] p;

    // Derive *d = new Derive;
    // delete d;
    // Derive d;
    return 0;
}