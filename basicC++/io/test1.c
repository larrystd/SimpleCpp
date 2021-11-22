#include <stdio.h>

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    printf("%#x \n", &n);
    int a[n];
    printf("size: %d\n", sizeof(a));
    for (int i = 0; i < n; i++) {
        a[i] = i;
        printf("%d \n", a[i]);
        printf("%#x \n", a+i);
    }

    return 0;
}