/*
 有个计算机组成原理，int小于等于数据线宽度，size_t大于等于地址线宽度。
 目前int一般为32位4bytes,size_t一般为64位8bytes。



 使用size_t可以提高代码的可移植性，有效性
 许多C库函数，例如malloc, memcpy, strlen返回值类型为size_t的类型。

 void* malloc (size_t n)
 void* memcpy (void* s1, void const* s2, size_t n)
 size_t strlen(char const* s)

 */