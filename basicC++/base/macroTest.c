#define CALL_WITH_MAX(a,b) ((a) > (b) ? (a) : (b))

#include <stdio.h>


int main(){
    int a = 5, b = 0;
    printf("%d\n", CALL_WITH_MAX(++a, b));
    printf("%d\n",CALL_WITH_MAX(++a,b+4));
    return 0;
}