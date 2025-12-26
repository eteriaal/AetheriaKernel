global irq0_handler_asm
extern pit_callback
extern pic_send_eoi

section .text
irq0_handler_asm:
    pusha
    call pit_callback
    mov al, 0
    call pic_send_eoi
    popa
    iretd