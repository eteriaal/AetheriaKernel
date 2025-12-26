#include "graphics.h"
#include "ports.h"
#include <stdbool.h>
#include "utils.h"
#include "keyboard.h"
#include "shell.h"

#define INPUT_BUFFER_SIZE 256

static char input_buffer[INPUT_BUFFER_SIZE];
static int input_index = 0;

void print_prompt_edit() {
    print("edit                                aetheria \n", make_color(COLOR_LIGHT_RED, COLOR_BLACK));
    print("--------------------------------------------------------------------------------", make_color(COLOR_WHITE, COLOR_BLACK));
}

void handle_input_char_edit(char c) {
    if (c == '\n') {
        input_buffer[input_index] = '\0';
        print("\n", make_color(COLOR_WHITE, COLOR_BLACK));
    } else if (c == '\b') {
        if (input_index > 0) {
            input_index--;
            print("\b \b", make_color(COLOR_WHITE, COLOR_BLACK));
        }
    } else if (c >= 32 && c <= 126) {  
        if (input_index < INPUT_BUFFER_SIZE - 1) {
            input_buffer[input_index++] = c;
            char str[2] = {c, '\0'};
            print(str, make_color(COLOR_LIGHT_GREEN, COLOR_BLACK));
        }
    }
}

void launch_edit() {
    clear_input_buffer();
    clear_screen(make_color(COLOR_WHITE, COLOR_BLACK));
    print_prompt_edit();

    while (1) {
        char c = get_char(); 
        if (c) {
            handle_input_char_edit(c);
        }
    }
}
