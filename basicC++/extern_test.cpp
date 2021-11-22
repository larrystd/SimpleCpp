#include<stdio.h>
 
int func();
 
int main()
{
    func(); //1
    extern int num; // 这里是声明, 说明变量在别的地方(后面), 去别的地方找
    printf("%d",num); //2
    return 0;
}
 
int num2 = 3;
 
int func()
{
    printf("%d\n",num);
}