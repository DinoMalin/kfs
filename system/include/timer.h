#pragma once

# define PIT_DATA    0x40
# define PIT_CMD     0x43

# define SET_DIVISOR    0b00110110
# define BASIC_RATE     1193180

# define RATE 100

void timer_install();
void wait(unsigned int wait_ticks);