#include <stdint.h>
#include "graphics.h"

int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (unsigned char)(*s1) - (unsigned char)(*s2);
}

unsigned int strlen(const char* s) {
    unsigned int len = 0;
    while (s[len]) len++;
    return len;
}

void print_number(uint8_t num) {
    char buffer[3] = {0};
    buffer[0] = (num / 10) + '0';
    buffer[1] = (num % 10) + '0';
    print(buffer, make_color(COLOR_LIGHT_CYAN, COLOR_BLACK));
}