#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <memory>

using namespace std;

template  <typename T>
T add(T a, T b) {
    return a+b;
}

int main() {
    int i1 = 1;
    int i2 = 2;
    cout << add<int>(i1,i2)<<endl;
    string s1 = "123";
    string s2("456");
    cout << add(s1, s2) <<endl;

    list<int> l;
    l.emplace_back(1);
    l.emplace_back(2);

    vector<int> v;
    v.assign(l.begin(), l.end());

    list<int> v_l;
    v_l.assign(v.begin(), v.end());
    for (auto& e:v_l) {
        cout << e << " ";
    }

    shared_ptr
    return 0;
}