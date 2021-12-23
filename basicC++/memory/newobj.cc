#include <iostream>
#include <string>
#include <new>
using namespace std;

class X
{
public:
    X() { cout<<"constructor of X"<<endl; }
    ~X() { cout<<"destructor of X"<<endl;}

    int x;
private:
    int num;
};

int main()
{
    X *px = new X;
    px->x = 1;
    cout << px->x<<endl;
    delete px;

    return 0;
}