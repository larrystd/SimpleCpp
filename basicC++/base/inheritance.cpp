#include <iostream>
using namespace std;


class Base{
public:
    Base(int t) : a(t){
        cout << "construct Base class of t" <<endl;
    }
    Base() : a(0){
        cout << "construct Base class" <<endl;
    }

    void output() const {
        cout << "This is base class"<<endl;
    }
    static void output_static(){
        cout << "This is static base class"<<endl;
    }
    int a;

};

class Derive : public Base{
public:
    Derive():Base(2){
        this->a = 3;
        
        
        cout << "construct derive class" <<endl;
    }
    void output() const {
        cout << "This is derived class"<<endl;
    }
    static void output_static() {
        cout << "This is static derived class"<<endl;
    }
};


int main(){
    Derive *d = new Derive();
    cout << d -> a <<endl;
    return 0;
}