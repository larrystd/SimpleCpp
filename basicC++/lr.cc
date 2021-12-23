#include <iostream>

using namespace std;

int&& sum(int a, int b) {
    return std::move(a+b);
}

int main() {
    int b =1;
    int &a = b;
    int c = a;  // 左值引用赋给左值
    cout << c <<endl;
    int&& ra  = 1;

    int suma = 1;
    int sumb = 10;
    int&& sumc = sum(suma, sumb);
    cout << sumc<<endl;


    return 0;
}