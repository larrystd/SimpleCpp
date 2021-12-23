//#include <stdexcept>
#include <limits>
#include <iostream>
#include <exception>
#include <vector>
#include <string>
using namespace std;

void MyFunc(int c)
{
    if (c > numeric_limits< char> ::max())
        throw invalid_argument("MyFunc argument too large.");
}

int main()
{
    try
    {
        MyFunc(256); //cause an exception to throw
    }

    catch (invalid_argument& e)
    {
        cerr << e.what() << endl;
    }
    vector<int> a;
    a.push_back
    MyFunc(10);

    string s;
    s.push_back
    MyFunc(128);
    //...
    return 0;
}