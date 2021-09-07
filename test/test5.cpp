#include <cstdio>

int d = 5;

int main()
{
    const int a  = 2;
    int* p = (int*)(&a);
    *p = 30;
    printf("%x\n",&a);
    printf("%x\n",p);
    printf("%i\n",a);
    printf("%i\n",*p);
    printf("%d\n", ::d);
    return 0;
}

/*运行结果
------------
61fe14
61fe14
30
30
------------*/

