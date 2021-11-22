#include <iostream>

// 计算 N 的阶乘 N!
template<int N>
class aTMP{
public:
    enum { ret = N * aTMP<N-1>::ret };
};
template<>
class aTMP<0>{
public:
    enum { ret = 1 };
};

int main(){
    std::cout << aTMP<10>::ret << '\n';
    std::cin.get(); return 0;
}