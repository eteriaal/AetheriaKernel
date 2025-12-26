#include "graphics.h"
#include "pit.h"
#include "ports.h"
#include "pic.h"
#include "idt.h"
#include "multiboot.h"
#include "shell.h"
#include "keyboard.h"  

extern uint32_t stack_space;

void kernel_main() {

    clear_screen(make_color(COLOR_WHITE, COLOR_BLACK));

    pic_remap(0x20, 0x28);    
    init_idt();               
    init_keyboard();          
    init_pit(100);            
    asm volatile ("sti");     

    print("Welcome to Aetheria Kernel\n", make_color(COLOR_LIGHT_RED, COLOR_BLACK));
	sleep(50);

    print("[KERNEL]", make_color(COLOR_LIGHT_RED,COLOR_BLACK));
    print(" ---> ", make_color(COLOR_LIGHT_BLUE, COLOR_BLACK));
    sleep(10);
    print("Kernel loaded! Opening shell in: ", make_color(COLOR_LIGHT_GREEN, COLOR_BLACK));

    sleep(50);
    print("3 ", make_color(COLOR_LIGHT_GREEN, COLOR_BLACK));
    sleep(50);
    print("2 ", make_color(COLOR_LIGHT_GREEN, COLOR_BLACK));
    sleep(50);
    print("1 \n", make_color(COLOR_LIGHT_GREEN, COLOR_BLACK));
	sleep(75);
    launch_shell();  
}
