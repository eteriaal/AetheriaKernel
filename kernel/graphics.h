#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((volatile uint8_t*)0xB8000)

enum VGA_Color {
    COLOR_BLACK         = 0x0,
    COLOR_BLUE          = 0x1,
    COLOR_GREEN         = 0x2,
    COLOR_CYAN          = 0x3,
    COLOR_RED           = 0x4,
    COLOR_MAGENTA       = 0x5,
    COLOR_BROWN         = 0x6,
    COLOR_LIGHT_GRAY    = 0x7,
    COLOR_DARK_GRAY     = 0x8,
    COLOR_LIGHT_BLUE    = 0x9,
    COLOR_LIGHT_GREEN   = 0xA,
    COLOR_LIGHT_CYAN    = 0xB,
    COLOR_LIGHT_RED     = 0xC,
    COLOR_PINK          = 0xD,
    COLOR_YELLOW        = 0xE,
    COLOR_WHITE         = 0xF
};

uint8_t make_color(enum VGA_Color fg, enum VGA_Color bg);
void graphics_init(void);
void clear_screen(uint8_t color);
void put_char_at(char c, uint8_t color, int x, int y);
void print_at(const char* str, uint8_t color, int x, int y);
void print(const char* str, uint8_t color);

#endif 
