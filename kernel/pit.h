#ifndef PIT_H
#define PIT_H

#include <stdint.h>

void init_pit(uint32_t frequency);
void sleep(uint32_t ticks); 

#endif
