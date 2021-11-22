#include <iostream>
#include <string>
using namespace std;

class X
{
public:
    X() { cout<<"constructor of X"<<endl; }
    ~X() { cout<<"destructor of X"<<endl;}

    void* operator new(size_t size,string str)
    {
        cout<<"operator new size "<<size<<" with string "<<str<<endl;
        return ::operator new(size);
    }

    void operator delete(void* pointee)
    {
        cout<<"operator delete"<<endl;
        ::operator delete(pointee);
    }

    int x;
private:
    int num;
};

int main()
{
    X *px = new("A new class") X;
    px->x = 1;
    cout << px->x<<endl;
    delete px;

    return 0;
}