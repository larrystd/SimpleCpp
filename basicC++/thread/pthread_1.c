/* example.c*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include<sys/syscall.h>

pid_t gettid()
{
    return syscall(SYS_gettid);
}
void thread(void)
{
    int i;
    printf("This is son, the pid is:%d, the tid is:%d\n", getpid(),gettid());

    sleep(3);
}

int main(int argc,char **argv)
{
    pthread_t id;
    int i,ret;
    ret=pthread_create(&id,NULL,(void *) thread,NULL);
    if(ret!=0){
        printf ("Create pthread error!\n");
        exit (1);
    }
    printf("This is master, the pid is:%d, the tid is:%d\n", getpid(),gettid());
    pthread_join(id,NULL);
    return 0;
}