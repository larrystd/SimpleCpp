#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class A {
public:
    int a_;
    A(): a_(6){}
    A(int a): a_(a) {}
};

int main() {
    A* p = new A();
    auto sa = make_shared<A>();
    cout << sa->a_ <<endl;
    auto sb = make_shared<A>(5);
    cout << sb->a_ <<endl;
    return 0;
}