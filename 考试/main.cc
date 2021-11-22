#include <stdio.h>
#include <iostream>


void print(int** p) {
    **p = 10;
    printf("%d\n", **p);
}

int main() {
    int a[] = {1,2,3,4};
    //print(&a);
    int* b = a;
    print(&b);
    int** c = &b;

    printf ("%d\n", *c);
    printf("%d %d\n", a[0], *(a+0));
    //printf("%x \n", **p);

    int buf[2][2]={{1,2},{3,4}};
    // char **p = buf;
    int (*p)[2] = buf;
    printf("buf[] = %d,%d,%d,%d\r\n",p[0][0],p[0][1],p[1][0],p[1][1]);
    printf("buf[] = %d,%d,%d,%d\r\n",(*p)[0],(*p)[1],(*(p+1))[0],(*(p+1))[1]);
    // printf("%d\n", (*p)[0]);
    return 0;
}