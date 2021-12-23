#include<iostream>
#include<vector>
#include<string>
#include<ctime>//将时间格式的数据转换成字符串
#include<chrono>
using namespace std::chrono;
using namespace std;
int main()
{
    //获取系统的当前时间
    auto t = system_clock::now();
    //将获取的时间转换成time_t类型
    auto tNow = system_clock::to_time_t(t);

    //ctime()函数将time_t类型的时间转化成字符串格式,这个字符串自带换行符
    string str_time = std::ctime(&tNow);

    cout<<str_time;

    return 0;
}