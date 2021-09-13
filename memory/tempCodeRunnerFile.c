#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{

        void* tstart = sbrk(0); //  起始地址
        printf ("heap start: %p\n", tstart);

        char* pmem = (char *)malloc(64);  //分配内存, 返回起始地址
        if (pmem == NULL) {
                perror("malloc");
                exit (EXIT_FAILURE);
        }
        printf ("pmem:%p\n", pmem);
        
        void *tend = sbrk(0);
        printf("head end: %p\n", tend);
        if (tend != (void *)-1)  // (void*) - 1 意思是是把-1转换成指针0xFFFFFFFF
                printf ("heap size on each load: %p\n", tend - tstart);
        free(pmem);
        return 0;
}