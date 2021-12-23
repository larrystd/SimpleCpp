#include <stdio.h>  
   
#define NAME(n) name_##n  
   
int main()  
{  

    int NAME(a);   // 相当于定义name_a
    int NAME(b);   // name_b
      
    NAME(a) = 520;  
    NAME(b) = 111;  
      
    printf("%d\n", NAME(a));  
    printf("%d\n", NAME(b));  

    int a[3];
    a[1] = 1;
    a[3]=4;
   
    return 0;  
}