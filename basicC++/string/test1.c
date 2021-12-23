#include <stdio.h>
#include <string.h>

int main() {
    int d = 1;
    char s[10];
    sprintf(s, "%d", d);
    printf("%s", s);
    return 0;
}