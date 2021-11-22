#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <errno.h>
#include <sys/stat.h>
#include<sys/syscall.h>

pid_t gettid()
{
    return syscall(SYS_gettid);
}


#define FIBER_STACK 8192
int a;
void * stack;

int do_something()
{
    printf("This is son, the pid is:%d, the tid is:%d, the a is: %d\n", getpid(),gettid(), ++a);
    free(stack);
    exit(1);
}

int main()
{
    void * stack;
    a = 1;
    stack = malloc(FIBER_STACK);//为子进程申请系统堆栈

    if(!stack)
    {
        printf("The stack failed\n");
        exit(0);
    }
    printf("creating son thread!!!\n");

    clone(&do_something, (char *)stack + FIBER_STACK, CLONE_VM|CLONE_SIGHAND|CLONE_THREAD, 0);//创建子线程

    printf("This is father, my pid is: %d, the tid is:%d, the a is: %d\n", getpid(),gettid(), a);
    exit(1);
}