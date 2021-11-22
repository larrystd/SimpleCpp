#include <stdio.h>
#include <string.h>

int main ()
{
   int len;
   const char str1[] = "ABCDEFG019874";
   const char str2[] = "BCD";

   len = strspn(str1, str2);

   printf("初始段匹配长度 %d\n", len );
   
   return(0);
}