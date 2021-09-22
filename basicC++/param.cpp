#include <iostream>
#include <vector>
#include <cassert>
#include <memory>

using namespace std;

template<typename T>
int fun(T&& a, T&& b) {
    cout << a<<endl;
}

int main() {
    int a = 1;
    fun(a,a);

    vector<int> vect = {1,2,3,4};

    int b = vect[0];
    int& b2 = vect[0];
    //int&& b = vect[0];
    //size_t& size = vect.size();
    //int& capaity = vect.capacity();
    int&& c = 1;

    auto&& iter = vect.begin();
    //vector<int>&& num = *vect.begin();

    //cout << size<<endl;

    int aa =1;
    //int& bb = a;
    //int& cc = a;
    //bb++;
    //cout << cc<<endl;
    cout << aa<<endl;
    cout << &aa<<endl;

    int&& bb = 1;
    cout << bb<<endl;
    cout << &bb<<endl;

    //int& dd = bb;

    // int c;
    //int && d = c; 右值引用不能绑定左值

    ///auto&& p = std::make_unique<int>(1);

    auto p = 1;
    /// std::move可以将左值转为右值引用
    /// q也是个左值, 
    //int &&n = 1;
    // int& q = n;

    int&& q = std::move(p);  /// 左值转换成右值


    int& p1 = p;
    int&& q1 = std::move(p1);  /// 左值转换成右值
    /*
    assert(p == nullptr);  // OK: reset to default
    q.reset(new int{2});   // or p = std::make_unique<int>(2);
    assert(*p == 2);       // OK: reset to int*(2
    */
    return 0;
}