#include <iostream>
#include <set>

using namespace std;

struct foo {
    int a;
    int b;
}f1, f2;

class A {
private:
    int x;
public:   
    A(int a) {
        this->x = a;
    }

    bool operator < (const A& b) const {
        if (this->x < b.x)
            return true;
        return false;
    }
};



int main() {

    A a1(1), a2(2);
    set<A> s;
    cout << "hello" <<endl;
    s.insert(a1);
    s.insert(a2);
    //cout << a1 == a2 <<endl;
    return 0;
}