#include <iostream>

using namespace std;

class Test {
public:
    Test(int a) : a_(a) {}

    void print() {
        cout << a_ <<endl;
    }
    ~Test() {
        cout << "destructor" <<endl;
    }
private:
    int a_;
};

int main () {
    Test test(1);
    test.print();
    return 0;
}
