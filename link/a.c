#include <stdio.h>

int shared;

int main() {
    int a = 100;
    swap(&a, &shared);

    printf("%d\n", a);
    printf("%d\n", shared);
    return 0;
}