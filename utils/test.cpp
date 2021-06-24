#include <iostream>
#include <thread>

#include "include/cmd.h"
#include "include/defer.h"
#include "include/noncopyable.h"
#include "include/mystrings.h"

// 默认是private继承，禁止运行时多态即 kvr::NonCopyAble x = new Test(); 会出现编译错误
class Test : kvr::NonCopyAble {
   public:
    Test() { std::cout << "Test constructor" << std::endl; }

    void Print() { std::cout << "Test " << std::endl; }

    ~Test() { std::cout << "Test deconstructor " << std::endl; }
};

// 重载cout << 
// 可以执行 cout << vector

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    if (v.empty()) {
        return os;
    }
    os << v.front();

    for (std::size_t i = 1; i < v.size(); ++i) {
        os << ' ' << v[i];
    }
    return os;
}


int main() {
    Test a;
    //WZQ_DEFER { a.Print(); };
    std::cout << "2" << std::endl;

    std::cout << kvr::Command::RunCmd("ls");

    std::vector<std::string> words = {"What", "a", "beautiful", "world"};
    std::cout << words << '\n';

    return 0;
}