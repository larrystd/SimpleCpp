#include <memory>
#include <iostream>
#include <functional>

using namespace std;

class B{

public:

int m_iNum;

};

int main() {

    const B* b1;

    //b1.m_iNum = 100; //comile error

    B* b2 = const_cast<B*>(b1);

    b2-> m_iNum = 200; //fine
}