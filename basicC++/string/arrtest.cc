#include <iostream>
//需要引入 array 头文件
#include <array>
using namespace std;
int main()
{
    //std::array<int, 4> values{};
    std::array<int, 4> values{};
    //初始化 values 容器为 {0,1,2,3}
    for (int i = 0; i < values.size(); i++) {
        values.at(i) = i;
    }
    //使用 get() 重载函数输出指定位置元素
    cout << get<3>(values) << endl;
    //如果容器不为空，则输出容器中所有的元素
    if (!values.empty()) {
        for (auto val = values.begin(); val < values.end(); val++) {
            cout << *val << " ";
        }
    }

    int& a = values[2];
    a = 100;
    cout << values.at(2);
}