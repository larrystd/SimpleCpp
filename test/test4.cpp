#include <iostream>

using namespace std;



class Test {
public:
    const int SIZE = 100;
    //int  array[SIZE];
    void print() {
        cout << SIZE <<endl;
    }
};

int main() {
    Test test;
    test.print();

    int n = 5;
    int array[n];

    return 0;
}