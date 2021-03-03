#include <iostream>
using namespace std;


class Base{
public:
    void output() const {
        cout << "This is base class"<<endl;
    }
    static void output_static(){
        cout << "This is static base class"<<endl;
    }
    virtual void interface() const = 0;
};

class Derive : public Base{
public:
    virtual void interface() const;
    void output() const {
        cout << "This is derived class"<<endl;
    }
    static void output_static() {
        cout << "This is static derived class"<<endl;
    }
};

inline void Base::interface() const {
    cout << "This is virtual function called interface()"<<endl;
}

inline void Derive::interface() const {
    Base::interface();
    Base::output();
}


const int* integer_return (const int& a){
    return &a;
}

int main(){
    Base::output_static();
    Derive *p = new Derive();
    p -> interface();
    int b = 3;
    const int* a = integer_return(b);

    cout<< *a <<endl;
    return 0;
}