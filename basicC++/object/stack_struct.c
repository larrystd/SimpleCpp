#include <stdio.h>

struct Test {
    int a;
    char b;
};

int main() {
    struct Test test;
    test.a = 1;
    test.b = 'a';
    printf("%d\n", test.b);

    return 0;
}