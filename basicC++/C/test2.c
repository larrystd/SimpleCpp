#include <stdio.h>

struct __attribute__ ((aligned(8))) myStruct1 {
	short f[3];
};

struct __attribute__ ((aligned(4))) myStruct2 {
	short f[3];
};

struct __attribute__ ((aligned(16))) myStruct3 {
	short f[3];
};

struct Test {
	short ch;
	char i;
};

struct sc1 {
    char a;
    char *b;
};

struct __attribute__ ((__packed__)) sc3 {
    char a;
    char *b;
};


struct __attribute__ ((__packed__)) sdshdr5 {   // __attribute__((__packed__)) 相当于取消字节对齐，效率换空间
    unsigned char flags; /* 3 lsb of type, and 5 msb of string length */
    char buf[];
};


int main() {
    struct myStruct1 my_struct1;
    struct myStruct2 my_struct2;
    struct myStruct3 my_struct3;
    printf("%ld\n", sizeof(my_struct1));
    printf("%ld\n", sizeof(my_struct2));
    printf("%ld\n", sizeof(my_struct3));

    printf("sc1: sizeof-char*  = %ld\n", sizeof(struct sc1));


    printf("sc3: packed sizeof-char*  = %ld\n", sizeof(struct sc3));

    printf("%ld\n", sizeof(struct Test));

    printf ("%ld\n", sizeof(struct sdshdr5));
    return 0;
}