#include <memory>
#include <iostream>
#include <functional>

using namespace std;

struct Foo {
    void print_sum(int n1, int n2)
    {
        std::cout << n1/n2 << '\n';
    }
    int data = 10;
};
int main() 
{
    Foo foo;
    //auto f = std::bind(&Foo::print_sum, &foo, std::placeholders::_2, std::placeholders::_1);
    function<void(int, int)> f = std::bind(&Foo::print_sum, &foo, std::placeholders::_2, std::placeholders::_1);
    f(5,10); // 100
}