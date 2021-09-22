#include <iostream>
#include <vector>
#include <cassert>
#include <memory>
#include <string>

using namespace std;

template<typename T>
int fun(T& a) {
    int b = 3;
    int& d =b;
    int& c = std::move(d);
    c = 4;
    cout << b<<endl;
}

int main() {
    int a = 1;
    fun(a);
    return 0;
}