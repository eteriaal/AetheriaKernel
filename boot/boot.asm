section .multiboot
align 4
    dd 0x1BADB002
    dd 0x00000001
    dd -(0x1BADB002 + 0x00000001)

section .text
global start
extern kernel_main
extern stack_space

start:
    cli
    mov esp, stack_space
    call kernel_main
    hlt
