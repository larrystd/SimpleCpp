#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <stdio.h>

// 1、-fPIC 作用于编译阶段，在编译动态库时(.so文件)告诉编译器产生与位置无关代码(Position-Independent Code)，若未指定-fPIC选项编译.so文件，则在加载动态库时需进行重定向。
class Test{
    private:
        double _calculate(int a, double b);
    public:
        double calculate(int a, double b, char c[], int * d, double * e, char ** f);
};

double Test::_calculate(int a, double b){
    double res = a+b;
    std::cout<<"res: "<<res<<std::endl;
    return res;
}

double Test::calculate(int a, double b, char c[], int * d, double * e, char ** f){
    std::cout<<"a: "<<a<<std::endl;
    std::cout<<"b: "<<b<<std::endl;
    std::cout<<"c: "<<c<<std::endl;
    std::cout<<"d: "<<d[0]<<d[1]<<std::endl;
    std::cout<<"e: "<<e[0]<<e[1]<<std::endl;
    std::cout<<"f: "<<f[0]<<f[1]<<std::endl;
    return this->_calculate(a, b);
}


// 封装C接口
extern "C"{
// 创建对象
    Test* test_new(){
        return new Test;
    }
    double my_calculate(Test* t, int a, double b, char c[], int * d, double * e, char ** f){
        return t->calculate(a, b,c,d,e,f);
    }
}

/*
 extern "C"的真实目的是实现类C和C++的混合编程。extern “C”是由Ｃ＋＋提供的一个连接交换指定符号，用于告诉Ｃ＋＋这段代码是Ｃ函数。extern “C”后面的函数不使用的C++的名字修饰,而是用C。
 
 
 C++语言支持函数重载，C语言不支持函数重载。函数被C++编译后在库中的名字与C语言的不同。假设某个函数的原型为：void foo(int x, int y);该函数被C编译器编译后在库中的名字为_foo，而C++编译器则会产生像_foo_int_int之类的名字。C++提供了C连接交换指定符号extern“C”来解决名字匹配问题。

与extern对应的关键字是static，被它修饰的全局变量和函数只能在本模块中使用。因此，一个函数或变量只可能被本模块使用时，其不可能被extern “C”修饰。

在C++源文件中的语句前面加上extern "C"，表明它按照类C的编译和连接规约来编译和连接，而不是C++的编译的连接规约。这样在类C的代码中就可以调用C++的函数or变量等

https://www.cnblogs.com/skynet/archive/2010/07/10/1774964.html
*/