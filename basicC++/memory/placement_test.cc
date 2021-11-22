#include <iostream>
using namespace std;

class X
{
public:
    X() { cout<<"constructor of X"<<endl; }
    ~X() { cout<<"destructor of X"<<endl;}

    void SetNum(int n)
    {
        num = n;
    }

    int GetNum()
    {
        return num;
    }

private:
    int num;
};

int main()
{
    char* buf = new char[sizeof(X)];
    cout << sizeof(*buf)<<endl;
    X *px = new(buf) X;
    px->SetNum(10);
    cout<<px->GetNum()<<endl;
    px->~X();
    delete []buf;

    return 0;
}