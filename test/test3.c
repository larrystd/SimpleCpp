#include<stdio.h>
struct
{
    int i;    
    char c1;  
    char c2;  
}x1;

struct{
    char c1;  
    int i;    
    char c2;  
}x2;

struct{
    char c1;  
    char c2; 
    int i;    
}x3;

struct{
    char c1; 
    short c3; 
    int i;    
}x4;

struct{
    char c1;  
    char c2; 
    char c3;    
}x5;


struct{
    int c1;  
    char c2; 
    short c3;    
    char c4;
}x6;


int main()
{
    printf("%d\n",sizeof(x1));  // 输出8
    printf("%d\n",sizeof(x2));  // 输出12
    printf("%d\n",sizeof(x3));  // 输出8
    printf("%d\n",sizeof(x4));  // 输出8
    printf("%d\n",sizeof(x5));  // 输出3
    printf("%d\n",sizeof(x6));  // 输出3
    return 0;
}