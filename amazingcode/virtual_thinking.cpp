/*
虚函数到底慢嘛？
编译器在编译时通常并不知道它将要调用哪个函数，所以它不能被内联优化和其它很多优化，因此就会增加很多无意义的指令（准备寄存器、调用函数、保存状态等），
而且如果虚函数有很多实现方法，那分支预测的成功率也会降低很多，分支预测错误也会导致程序性能下降。
*/

#include <cmath>
#include <ctime>
struct Base {
   public:
    virtual int f(double i1, int i2) { return static_cast<int>(i1 * log(i1)) * i2; }
};

int main() {
    TimerLog t("timer");
    Base *a = new Base();
    int ai = 0;
    for (int i = 0; i < 1000000000; i++) {
        ai += a->f(i, 10);
    }
    cout << ai << endl;
}