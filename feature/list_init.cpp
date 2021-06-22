/*
cpp11的列表初始化
cpp11中在变量名后面加上初始化列表进行对象的初始化
*/

struct A {
public:
    A(int) {}
private:
    A(const A&) {}
};

int main() {
    A a(123);
    // A b = 123; 编译失败，这实际上是拷贝构造
    A c = {123};

    return 0;
}

// 聚合类型可以直接列表初始化
/*
聚合类型

1. 类型是一个普通数组，如int[5], char[]
2. 类型是一个类，且满足
没有用户声明的构造函数
没有private或者protected保护的非静态数据成员
没有基类
没有虚函数
*/