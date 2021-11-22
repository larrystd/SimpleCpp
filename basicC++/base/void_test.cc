#include <iostream>

using namespace std;

int main() {
    int b = 1;
    int* a = &b;
    void* c = (void* )a;
    cout << *(int*) c<<endl;

    return 0;
}