#include <iostream>
#include <vector>
#include <cassert>
#include <memory>
#include <string>

using namespace std;

template<typename T>
int fun(T& a) {
    int&& b = 3;
    a = std::move(b);
    a = 4;
    cout << b<<endl;

    //int c = 4;
    //a = c;
    //int&& c = a;
    int& c =  std::move(b);
    //cout << type_info(a) <<endl;
    ///cout << typeid(b)<<endl;
}

int main() {
    int a = 1;
    fun(a);
    cout << a<<endl;

    int d = 2;
    int d2 = 5;
    int& e1 = d;
    e1 = d2;
    cout << e1<<endl;

    string str1="a";
    string str3="b";
    string &str2=str1;
    str2=str3;
    cout << str2<<endl;
    cout << str1<<endl;

    string&& str4="a";
    str4="b";

    cout << str4<<endl;
    cout << str4<<endl;

    string str5 = str2;
    string& str6 = str2;
    str6 = "c";
    cout << str6<<endl;
    cout <<str2<<endl;
    cout <<str1<<endl;
    
    return 0;
}