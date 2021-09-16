#include <iostream>
 
#include <string>
 
using namespace std;
 
 
 
// 定义函数指针pf
 
int (*pf)(const int&, const int&);
 
 
 
// 定义函数指针类型cmpFun
 
typedef int (*cmpFun)(const int&, const int&);
 
 
 
// 具体函数
 
int intCompare(const int& aInt, const int& bInt)
 
{
 
         if(aInt == bInt) return 0;
 
         if(aInt > bInt) 
 
         {
 
                   return 1;
 
         }
 
         else
 
         {
 
                   return -1;
 
         }
 
}
 
 
 
int main(void)
 
{
 
         int aInt = 1;
 
         int bInt = 2;
 
 
 
         cmpFun pf = intCompare;
 
         // pf = &stringCompare;              // 和上面一句是完全一样的
 
        cout << pf(aInt, bInt)<<endl;

 
         // 使用pf
 
 
         return 0;
 
}