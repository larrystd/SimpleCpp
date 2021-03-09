#include<iostream>
using namespace std;
//函数模板
//普通函数模板fm
template<typename T>
T fm(T t1)
{
  cout<<"普通函数模板"<<endl;
  return t1;
}
//fm的指针特化模板
template<typename T>
T* fm(T* t1)
{
  cout<<"int指针特化模板"<<endl;
  return t1;
}
//fm的int特化模板
template<>
int fm(int t1)
{
  cout<<"int特化函数模板"<<endl;
  return t1;
}
template<>
float fm(float t1)
{
  cout<<"float特化模板"<<endl;
  return t1;
}
//普通类模板Test
template<typename T1,typename T2>
class Test
{
public:
  void ply()
  {
    cout<<"普通类模板"<<endl;
  }
};
template<typename T1>
class Test<T1,int>
{
public:
  void ply()
  {
    cout<<"int偏特化类模板"<<endl;

  }
};
template<>
class Test<char,int>
{
public:
  void ply()
  {
    cout<<"全特化类模板"<<endl;
  }
};
//测试程序
int main()
{
  int a =23;
  int *p =&a;

  cout<<fm(a)<<endl;
  cout<<fm(p)<<endl;
  float f =23.4;
  cout<<fm(f)<<endl;
  double d= 99.45;
  cout<<fm(d)<<endl;
  cout<<endl;
  Test<char,char>TT1;
  TT1.ply();
  Test<int*,int>TT2;
  TT2.ply();
  Test<char,int>TT3;
  TT3.ply();
  return 0;
}