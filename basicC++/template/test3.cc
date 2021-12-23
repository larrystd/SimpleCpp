#include <iostream>
using namespace std;

#ifndef TEMPLATE_DEMO_HXX
#define TEMPLATE_DEMO_HXX
 
template<class T> class A{
    public:
        T g(T a,T b);
        A();
};
 
#endif
 
template<class T> A<T>::A(){}
 
template<class T> T A<T>::g(T a,T b){
    return a+b;
}
 
int main(){
    A<int>* a = new A<int>;
    cout<<a->g(2,3.2)<<endl;
}