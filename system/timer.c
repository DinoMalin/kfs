#include "timer.h"

unsigned int ticks = 0;

/* The clock by default run
 * at 1193180Hz, and trigger IRQ0
 * at a frequence of 18.2Hz.
 * We can choose to trigger IRQ0
 * on a custom rate : 100Hz is
 * more precise.
 */
void timer_phase(int hz) {
	int divisor = BASIC_RATE / hz;
	outb(PIT_CMD, SET_DIVISOR);
	outb(PIT_DATA, divisor & 0xFF);
	outb(PIT_DATA, divisor >> 8);
}

void timer_handler(struct regs *r) { ticks++; }

void timer_install() {
	timer_phase(RATE);
	irq_install_handler(0, timer_handler);
}

void wait(unsigned int wait_ticks) {
	unsigned int offset = ticks + wait_ticks;
	while (ticks < offset)
		;
}
