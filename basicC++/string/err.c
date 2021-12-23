#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
int main(){
        extern int errno;
        errno = 0;
        opendir("123456");
        printf("errno %d\n", errno);
        if(errno!=0){
                perror("opendir");
        }
        if(errno!=0){
                printf("%s\n", strerror(errno));
        }
        return 0;
}