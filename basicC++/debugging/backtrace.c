#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
void
myfunc(void)
{
   int j, nptrs;
#define SIZE 100
   void *buffer[100];
   char **strings;
 
   nptrs = backtrace(buffer, SIZE);  // 获取程序堆栈数据, npts为
   printf("backtrace() returned %d addresses\n", nptrs);
 
   /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
	  would produce similar output to the following: */
 
   strings = backtrace_symbols(buffer, nptrs);  //从backtrace()函数获取的地址buffer转为描述这些地址的字符串数组。backtrace_symbols为这些数组开辟了内存但不负责回收,strings是二维指针
   if (strings == NULL) {
	   perror("backtrace_symbols");
	   exit(EXIT_FAILURE);
   }
 

   for (j = 0; j < nptrs; j++)
      printf("  [%02d] %s\n", j, strings[j]);
   free(strings); // 这样就可以回收内存了
}
int
main(int argc, char *argv[])
{
   myfunc();
   exit(EXIT_SUCCESS);
}