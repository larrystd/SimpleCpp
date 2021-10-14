#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int num = 123456;
    char str[16] = {0};
    int n = sprintf(str, " %d" , num);
    printf("数字：%d 转换后的字符串为：%s\n",num,str);
    printf("长度为: %d\n", strlen(str));
    printf("返回为: %d\n", n);

    char str2[16] = {'1'};

    for (int i = 0; i < 10; i++) {
        printf("%c ", str2[i]);
    }
    return 0;
}