#include <stdio.h>
#include <unistd.h> // 使用brk/sbrk，需要使用这个头文件
int main()
{
    //存放数据
    int i = 2;
    int* phead; // 指向首位置
    int* pnow; // 指向当前指针位置
    pnow = sbrk(0); // 先分配空闲区域
    phead = pnow; // 固定首位置不变
    printf("pnow addr: %p\n", pnow);    // %p打印地址
    printf("phead addr: %p\n", phead);
    for(i=2; i<10; i++)
    {
        if(i > 5) // 该函数用于判断是否是素数
        {
           brk(pnow+4);// 堆的边界扩展
            *pnow = i; // 在pnow地址起始处存入数据
            pnow = sbrk(0); // pnow指向系统指针位置, 注意堆地址向上增长
            printf("pnow addr: %p\n", pnow);
        }
    }

    printf("pnow addr: %p\n", pnow);
    printf("phead addr: %p\n", phead);

    //打印数据
    pnow = phead; // phead
    while(pnow!=sbrk(0))
    {
        printf("%d\n",*pnow);
        pnow = pnow+4;
    }
    brk(phead); // brk指向phead 释放空间
}