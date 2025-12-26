#include "idt.h"
#include <stdint.h>

extern void irq0_handler_asm();
extern void irq1_handler_asm();

struct idt_entry {
    uint16_t base_low;
    uint16_t sel;
    uint8_t  always0;
    uint8_t  flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

#define IDT_ENTRIES 256
struct idt_entry idt[IDT_ENTRIES];
struct idt_ptr idtp;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
    idt[num].base_high = (base >> 16) & 0xFFFF;
}

static inline void lidt(void* base, uint16_t size) {
    struct {
        uint16_t length;
        void* addr;
    } __attribute__((packed)) idtr = { size, base };

    __asm__ volatile ("lidt %0" : : "m"(idtr));
}

void init_idt() {
    idtp.limit = (sizeof(struct idt_entry) * IDT_ENTRIES) - 1;
    idtp.base = (uint32_t)&idt;

    for (int i = 0; i < IDT_ENTRIES; i++) {
        idt_set_gate(i, 0, 0, 0);
    }
    
    idt_set_gate(0x20, (uint32_t)irq0_handler_asm, 0x08, 0x8E);

    idt_set_gate(0x21, (uint32_t)irq1_handler_asm, 0x08, 0x8E);

    lidt(&idt, idtp.limit);
}
