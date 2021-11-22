#include <iostream>

using namespace std;

int main() {
    int b =1;
    int &a = b;
    int c = a;
    cout << c <<endl;

    return 0;
}