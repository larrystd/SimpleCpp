#include <iostream>

using namespace std;

class YinWenHan {
public:
    YinWenHan(string& name) {
        this->name = name;
    }
    string name;
    
};

ostream& operator<< (ostream& out, YinWenHan& A) {
    out <<A.name<< "是美女老师";
}

int main() {
    string name;
    cin >> name;
    YinWenHan *y = new YinWenHan(name);
    cout << y <<endl;
    return 0;
}
