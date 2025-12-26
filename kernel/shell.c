#include "graphics.h"
#include "ports.h"
#include "shell.h"
#include <stdbool.h>
#include "utils.h"
#include "keyboard.h"  
#include "rtc.h"
#include "edit.h"

#define INPUT_BUFFER_SIZE 128

static char input_buffer[INPUT_BUFFER_SIZE];
static int input_index = 0;

void print_prompt() {
    print("$Aetheria$ > ", make_color(COLOR_LIGHT_GREEN, COLOR_BLACK));
}

void clear_input_buffer() {
    for (int i = 0; i < INPUT_BUFFER_SIZE; i++) input_buffer[i] = 0;
    input_index = 0;
}

void execute_command(const char* cmd) {
    if (!cmd || cmd[0] == '\0') return;

    if (strcmp(cmd, "help") == 0) {
        print("Available commands: help, clear, about, links, rtc, edit, halt\n", make_color(COLOR_LIGHT_CYAN, COLOR_BLACK));
    } else if (strcmp(cmd, "clear") == 0) {
        clear_screen(make_color(COLOR_BLACK, COLOR_BLACK));
    } else if (strcmp(cmd, "about") == 0) {
        print("Aetheria Shell v0.2 by eteriaal\n", make_color(COLOR_LIGHT_RED, COLOR_BLACK));
    } else if (strcmp(cmd, "halt") == 0) {
        print("Halting system...\n", make_color(COLOR_RED, COLOR_BLACK));
        asm volatile("cli");
        asm volatile ("hlt");
    } else if (strcmp(cmd, "edit") == 0) {
        launch_edit();
    } else if (strcmp(cmd, "links" ) == 0) {
        print("github: github.com/eteriaal/AetheriaKernel \n", make_color(COLOR_LIGHT_BLUE, COLOR_BLACK));
    } 
        else if (strcmp(cmd, "rtc") == 0) {
        uint8_t hour, minute, second, day, month, year;
        read_rtc(&hour, &minute, &second, &day, &month, &year);

        print("Current RTC time: ", make_color(COLOR_LIGHT_GREEN, COLOR_BLACK));
        print_number(hour);
        print(":", make_color(COLOR_LIGHT_GREEN, COLOR_BLACK));
        print_number(minute);
        print(":", make_color(COLOR_LIGHT_GREEN, COLOR_BLACK));
        print_number(second);
        print(" Date: ", make_color(COLOR_LIGHT_GREEN, COLOR_BLACK));
        print_number(day);
        print("/", make_color(COLOR_LIGHT_GREEN, COLOR_BLACK));
        print_number(month);
        print("/", make_color(COLOR_LIGHT_GREEN, COLOR_BLACK));
        print_number(year);
        print("\n", make_color(COLOR_LIGHT_GREEN, COLOR_BLACK));
    }
     else {
        print("Unknown command\n", make_color(COLOR_LIGHT_RED, COLOR_BLACK));
    }
}

void handle_input_char(char c) {
    if (c == '\n') {
        input_buffer[input_index] = '\0';
        print("\n", make_color(COLOR_WHITE, COLOR_BLACK));
        execute_command(input_buffer);
        clear_input_buffer();
        print_prompt();
    } else if (c == '\b') {
        if (input_index > 0) {
            input_index--;
            print("\b \b", make_color(COLOR_WHITE, COLOR_BLACK));
        }
    } else if (c >= 32 && c <= 126) {  
        if (input_index < INPUT_BUFFER_SIZE - 1) {
            input_buffer[input_index++] = c;
            char str[2] = {c, '\0'};
            print(str, make_color(COLOR_WHITE, COLOR_BLACK));
        }
    }
}


char get_char() {
    char c = get_last_key();
    return c;
}

void launch_shell() {
    clear_input_buffer();

    clear_screen(make_color(COLOR_WHITE, COLOR_BLACK));
    print("[SHELL]", make_color(COLOR_RED, COLOR_BLACK));
    print(" --> ", make_color(COLOR_LIGHT_BLUE, COLOR_BLACK));
    print("Welcome to Aetheria shell! Write help to help.\n", make_color(COLOR_LIGHT_GREEN, COLOR_BLACK));

    print_prompt();

    while (1) {
        char c = get_char(); 
        if (c) {
            handle_input_char(c);
        }
    }
}
