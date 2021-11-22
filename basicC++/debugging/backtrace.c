#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
void
myfunc3(void)
{
   int j, nptrs;
#define SIZE 100
   void *buffer[100];
   char **strings;
 
   nptrs = backtrace(buffer, SIZE);
   printf("backtrace() returned %d addresses\n", nptrs);
 
   /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
	  would produce similar output to the following: */
 
   strings = backtrace_symbols(buffer, nptrs);  //从backtrace()函数获取的地址buffer转为描述这些地址的字符串数组。
   if (strings == NULL) {
	   perror("backtrace_symbols");
	   exit(EXIT_FAILURE);
   }
 
   for (j = 0; j < nptrs; j++)
	   printf("%s\n", strings[j]);

    for (j = 0; j < nptrs; j++)
		printf("  [%02d] %s\n", j, strings[j]);
 
   free(strings);
}
 
static void   /* "static" means don't export the symbol... */
myfunc2(void)
{
   myfunc3();
}
 
void
myfunc(int ncalls)
{
   if (ncalls > 1)
	   myfunc(ncalls - 1);
   else
	   myfunc2();
}
 
int
main(int argc, char *argv[])
{
   if (argc != 2) {
	   fprintf(stderr, "%s num-calls\n", argv[0]);
	   exit(EXIT_FAILURE);
   }
 
   myfunc(atoi(argv[1]));
   exit(EXIT_SUCCESS);
}