#include <iostream>
#include <vector>
#include <cassert>
#include <memory>
#include <string>

using namespace std;

int fun() {
    int b = 1;
    int* a = &b;
    return *a;   // 就算a是指针, 但以返回类型int为准
}



int main() {
    int b = 3;

    int&& bb = 4;
    int&& a = static_cast<int&&>(1);
    //a++;
    cout << a<<endl;

    int& d = a;

    //double ret= fun();
    //cout << ret<<endl;
    return 0;
}