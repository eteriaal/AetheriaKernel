#include "rtc.h"
#include "ports.h"

static uint8_t cmos_read(uint8_t reg) {
    outb(0x70, reg);
    return inb(0x71);
}

static int is_updating() {
    outb(0x70, 0x0A);
    return inb(0x71) & 0x80;
}

static uint8_t bcd_to_bin(uint8_t val) {
    return (val & 0x0F) + ((val / 16) * 10);
}

void read_rtc(uint8_t* hour, uint8_t* minute, uint8_t* second,
              uint8_t* day, uint8_t* month, uint8_t* year) {
    while (is_updating());

    *second = cmos_read(0x00);
    *minute = cmos_read(0x02);
    *hour   = cmos_read(0x04);
    *day    = cmos_read(0x07);
    *month  = cmos_read(0x08);
    *year   = cmos_read(0x09);

    uint8_t reg_b = cmos_read(0x0B);

    if (!(reg_b & 0x04)) {
        *second = bcd_to_bin(*second);
        *minute = bcd_to_bin(*minute);
        *hour   = bcd_to_bin(*hour);
        *day    = bcd_to_bin(*day);
        *month  = bcd_to_bin(*month);
        *year   = bcd_to_bin(*year);
    }
}
