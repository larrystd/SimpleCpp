#include<iostream>
#include <functional>
using namespace std;

struct Foo {
    void print_sum(int n1, int n2)
    {
        std::cout << n1+n2 << '\n';
    }
    int data = 10;
};
int main() 
{
    Foo foo;
    std::function<void(int)> f = std::bind(&Foo::print_sum, &foo, 95, std::placeholders::_1);
    std::function<void(int,int)> f1 = std::bind(&Foo::print_sum, &foo, 95, std::placeholders::_1);
    f1(5); // 100
}