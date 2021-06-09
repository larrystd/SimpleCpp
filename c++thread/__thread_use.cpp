#include <iostream>
#include <pthread.h>
#include <unistd.h>


/*
thread变量每一个线程有一份独立实体，各个线程的值互不干扰。可以用来修饰那些带有全局性且值可能变，但是又不值得用全局变量保护的变量。
只能修饰POD类型(类似整型指针的标量，不带自定义的构造、拷贝、赋值、析构的类型，二进制内容可以任意复制memset,memcpy,且内容可以复原)

#pragma GCC diagnostic error "-Wuninitialized"
  foo(a);                       //error is given for this one
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
  foo(b);                       // no diagnostic for this one 
#pragma GCC diagnostic pop
  foo(c);                       // error is given for this one 
#pragma GCC diagnostic pop
  foo(d);                       // depends on command-line options 

std::bind 
// (_1 and _2 are from std::placeholders, and represent future
    // arguments that will be passed to f1)
    auto f1 = std::bind(f, _2, 42, _1, std::cref(n), n);
    n = 10;
    f1(1, 2, 1001); // 1 is bound by _1, 2 is bound by _2, 1001 is unused
                    // makes a call to f(2, 42, 1, n, 7)

*/
__thread int i = 0;     

void* f1(void* arg)
{
    i++;
    printf("f1 i address %p val %d\n", &i, i);
}

void* f2(void* arg)
{
    i += 2;
    printf("f2 i address %p val %d\n", &i, i);
    
}

int main()
{
    pthread_t pid1, pid2;
    i += 3;
    pthread_create(&pid1, NULL, f1, NULL);
    pthread_create(&pid2, NULL, f2, NULL);
    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);
    printf("main i address %p val %d\n", &i, i);

    return 0;
}