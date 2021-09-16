#include<cstdio>

using byte_pointer = char*;

using true_byte_pointer = unsigned char*;

template<class T>
void show_byte(T num, byte_pointer p) {
    unsigned int len = sizeof(T);
    /// 按字节输出
    for (int i = 0; i < len; ++i) {
        printf("%x  ", p[i]);
        ///printf("%uld  ", sizeof(p[i]));
    }
    puts("\n");
}

template<class T>
void true_show_byte(T num, true_byte_pointer p) {
    unsigned int len = sizeof(T);
    for (int i = 0; i < len; ++i) {
        printf("%d ", p[i]);
    }
    puts("");
}

int main() {
    short a = 3;   // 2字节, fffd
    short b = -1;   // 2字节, ffffffff
    int c = -3;     // 4字节
    int d = -1; // 4字节

    show_byte(a, (byte_pointer)&a);
    show_byte(b, (byte_pointer)&b);
    show_byte(c, (byte_pointer)&c);
    show_byte(d, (byte_pointer)&d);

    true_show_byte(a, (true_byte_pointer)&a);
    true_show_byte(b, (true_byte_pointer)&b);
    true_show_byte(c, (true_byte_pointer)&c);
    true_show_byte(d, (true_byte_pointer)&d);
    return 0;
}