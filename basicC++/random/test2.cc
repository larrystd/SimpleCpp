
#include <iostream>
#include <random>
using namespace std;
 
int main( ){
    default_random_engine e;
    uniform_int_distribution<unsigned> u(0, 9);
    for(int i=0; i<10; ++i)
        cout<<u(e)<<endl;
    return 0;
}