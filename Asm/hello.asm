global _start   ;全局声明

section .text  ; 定义代码段

_start:
    mov rax, 1  ; rax保存系统调用号。第1号系统调用即sys_write. size_t sys_write(unsigned int fd, const char * buf, size_t count);
    mov rdi, 1  ; 传递第一个参数给函数，是函数句柄，表示stdout。
    mov rsi, message    ; 第二个参数为message
    mov rdx, 13 ; 第三个参数
    syscall
    mov rax, 60 ; 60给rax寄存，第60号的系统调用是exit。
    xor rdi, rdi    ; 相当于mov rdi 0 传递0给rdi
    syscall

section .data   ; 数据段

message:
    db "Hello, World", 10   ; 10表示换行