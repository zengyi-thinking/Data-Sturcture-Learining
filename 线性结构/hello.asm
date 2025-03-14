; 输出 "HELLO ASM!" 并退出（x86_64 Linux示例）
section .data
    msg db 'HELLO ASM!', 0xA  ; 定义字符串 + 换行符
    len equ $ - msg           ; 计算字符串长度

section .text
    global _start

_start:
    ; 系统调用号: write(1)
    mov rax, 1      ; sys_write
    mov rdi, 1      ; stdout
    mov rsi, msg
    mov rdx, len
    syscall

    ; 系统调用号: exit(60)
    mov rax, 60     ; sys_exit
    xor rdi, rdi    ; 返回码0
    syscall