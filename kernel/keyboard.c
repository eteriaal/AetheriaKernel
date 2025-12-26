#include "keyboard.h"
#include "ports.h"
#include "idt.h"
#include "graphics.h"
#include <stdbool.h>

#define SC_MAX 128

extern void irq1_handler_asm();

static bool shift = false;
static bool caps_lock = false;

static char key_buffer[256];
static uint8_t key_index = 0;

static char last_key = 0;

static const char sc_ascii[SC_MAX] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`', 0,'\\',
    'z','x','c','v','b','n','m',',','.','/', 0,'*', 0,' ',
};

static const char sc_ascii_shift[SC_MAX] = {
    0,  27, '!','@','#','$','%','^','&','*','(',')','_','+','\b',
    '\t','Q','W','E','R','T','Y','U','I','O','P','{','}','\n', 0,
    'A','S','D','F','G','H','J','K','L',':','"','~', 0,'|',
    'Z','X','C','V','B','N','M','<','>','?', 0,'*', 0,' ',
};

void keyboard_callback() {
    uint8_t scancode = inb(0x60);

    bool key_released = scancode & 0x80;
    uint8_t key = scancode & 0x7F;

    if (!key_released) {
        
        if (key == 0x2A || key == 0x36) { 
            shift = true;
        } else if (key == 0x3A) { 
            caps_lock = !caps_lock;
        } else {
            
            char c;
            if (shift) {
                c = sc_ascii_shift[key];
            } else {
                c = sc_ascii[key];
            }

            
            if (caps_lock && c >= 'a' && c <= 'z') {
                c = c - 'a' + 'A';
            } else if (caps_lock && c >= 'A' && c <= 'Z') {
                c = c - 'A' + 'a';
            }

            if (c) {
                last_key = c;
                if (key_index < sizeof(key_buffer) - 1) {
                    key_buffer[key_index++] = c;
                }
            }
        }
    } else {
        
        if (key == 0x2A || key == 0x36) {
            shift = false;
        }
    }
    
    outb(0x20, 0x20);
}

void init_keyboard() {
    idt_set_gate(33, (uint32_t)irq1_handler_asm, 0x08, 0x8E);
    uint8_t mask = inb(0x21);
    outb(0x21, mask & ~(1 << 1));
}

char get_last_key() {
    char c = last_key;
    last_key = 0;
    return c;
}
