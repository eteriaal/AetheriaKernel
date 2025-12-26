#include "pit.h"
#include <stdint.h>
#include "ports.h"

volatile uint32_t pit_ticks = 0;

void pit_callback() {
    pit_ticks++;
}

void sleep(uint32_t ticks) {
    uint32_t start = pit_ticks;
    while (pit_ticks - start < ticks);
}

void init_pit(uint32_t frequency) {
    uint16_t divisor = 1193180 / frequency;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);       
    outb(0x40, (divisor >> 8) & 0xFF); 
}
