; ��� "HELLO ASM!" ���˳���x86_64 Linuxʾ����
section .data
    msg db 'HELLO ASM!', 0xA  ; �����ַ��� + ���з�
    len equ $ - msg           ; �����ַ�������

section .text
    global _start

_start:
    ; ϵͳ���ú�: write(1)
    mov rax, 1      ; sys_write
    mov rdi, 1      ; stdout
    mov rsi, msg
    mov rdx, len
    syscall

    ; ϵͳ���ú�: exit(60)
    mov rax, 60     ; sys_exit
    xor rdi, rdi    ; ������0
    syscall