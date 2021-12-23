#include <exception>
#include <iostream>

using namespace std;

void Throw()
{
    throw exception();
}

void NoBlockThrow()
{ Throw(); }

void BlockThrow() noexcept{ Throw(); }

int main()
{
    try {
        Throw();
    }
    catch(...) 
    {
        cout << "Found throw."<< endl; // Found throw
    }
    
    try {
        NoBlockThrow();
    }
    catch(...) 
    {
        cout << "Throw is notblocked" <<endl;
    }
    
    try {
        BlockThrow();
    }
    catch(...) {
        cout << "Found throw1" << endl;
    }
    return 0;
}

