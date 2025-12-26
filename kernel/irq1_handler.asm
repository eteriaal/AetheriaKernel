global irq1_handler_asm
extern keyboard_callback
extern pic_send_eoi

section .text
irq1_handler_asm:
    pushad
    call keyboard_callback
    mov al, 1        
    call pic_send_eoi
    popad
    iretd
