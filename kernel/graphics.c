#include "graphics.h"

static int cursor_x = 0;
static int cursor_y = 0;

uint8_t make_color(enum VGA_Color fg, enum VGA_Color bg) {
    return (bg << 4) | (fg & 0x0F);
}

void clear_screen(uint8_t color) {
    for (int y = 0; y < VGA_HEIGHT; ++y) {
        for (int x = 0; x < VGA_WIDTH; ++x) {
            put_char_at(' ', color, x, y);
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}

void put_char_at(char c, uint8_t color, int x, int y) {
    if (x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_HEIGHT)
        return;

    const size_t index = (y * VGA_WIDTH + x) * 2;
    VGA_MEMORY[index] = c;
    VGA_MEMORY[index + 1] = color;
}

void print_at(const char* str, uint8_t color, int x, int y) {
    for (int i = 0; str[i] != '\0'; ++i) {
        put_char_at(str[i], color, x + i, y);
    }
}

void scroll_up() {
    for (int y = 1; y < VGA_HEIGHT; ++y) {
        for (int x = 0; x < VGA_WIDTH; ++x) {
            size_t from = (y * VGA_WIDTH + x) * 2;
            size_t to = ((y - 1) * VGA_WIDTH + x) * 2;
            VGA_MEMORY[to] = VGA_MEMORY[from];
            VGA_MEMORY[to + 1] = VGA_MEMORY[from + 1];
        }
    }

    for (int x = 0; x < VGA_WIDTH; ++x) {
        size_t index = ((VGA_HEIGHT - 1) * VGA_WIDTH + x) * 2;
        VGA_MEMORY[index] = ' ';
        VGA_MEMORY[index + 1] = make_color(COLOR_WHITE, COLOR_BLACK);
    }

    if (cursor_y > 0)
        cursor_y--;
}

void print(const char* str, uint8_t color) {
    while (*str) {
        if (*str == '\n') {
            cursor_x = 0;
            cursor_y++;
        } else if (*str == '\b') {
            if (cursor_x > 0) {
                cursor_x--;
                put_char_at(' ', color, cursor_x, cursor_y);
            } else if (cursor_y > 0) {
                cursor_y--;
                cursor_x = VGA_WIDTH - 1;
                put_char_at(' ', color, cursor_x, cursor_y);
            }
        } else {
            put_char_at(*str, color, cursor_x, cursor_y);
            cursor_x++;
            if (cursor_x >= VGA_WIDTH) {
                cursor_x = 0;
                cursor_y++;
            }
        }

        if (cursor_y >= VGA_HEIGHT) {
            scroll_up();  
        }

        str++;
    }
}
