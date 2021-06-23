/*
std::function 和lambda表达式

使用std::function可以完全代替函数指针的形式
还可以结合std::bind一起使用

lambda表达式
[capture list] (params list) mutable exception-> return type { function body }

auto func2 = [](int a) -> int { return a + 2; }; 

capture list：捕获外部变量列表
params list：形参列表
mutable指示符：用来说用是否可以修改捕获的变量
exception：异常设定
return type：返回类型
function body：函数体
*/


#include <functional>
#include <iostream>

std::function<void(int)> f;// 表示f的参数为int, 返回值为void

struct Foo {
    Foo (int num) : num_(num) {}
    void print_add(int i) const {
        std::cout << num_ + i << "\n";
    }
    int num_;
};

void printNum (int i) {
    std::cout<<i <<std::endl;
}

struct PrintNum {
    void operator() (int i) const {
        std::cout << i << std::endl;
    }
};

int main() {
    std::function<void(int)> f_display = printNum;
    f_display(-9);

    std::function<void()> f_display_42 = []() {printNum(42);};
    f_display_42();

    std::function<void()> f_display_3133 = std::bind(printNum, 3133);
    f_display_3133();

    // 调用成员函数
    // 第一个参数为class
    std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
    const Foo foo(314);
    f_add_display(foo, 1);
    f_add_display(314, 2);


    using std::placeholders::_1;
    std::function<void(int)> f_add_display2 = std::bind(&Foo::print_add, foo, _1);
    f_add_display2(3);

    std::function<void(int)> f_add_display3 = std::bind(&Foo::print_add, &foo, _1);
    f_add_display3(4);

    // 调用重载()的对象
    std::function<void(int)> f_display_3 = PrintNum();
    f_display_3(18);

    return 0;
}