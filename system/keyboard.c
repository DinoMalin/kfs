#include "keyboard.h"

u8 kbus[256] = {US_KBMAP};
u8 kbfr[256] = {FR_KBMAP};
kbmap layout = US;

key_status ks = 0;
int enter = 0;

int shortcut(u8 scancode) {
	if (CTRL_SHORT('a', layout)) {
		auto_switch_workspace();
		return 1;
	}
	return 0;
}

int check_key(u8 scancode) {
	if (isshift(scancode)) {
		ks ^= shift;
		return 1;
	} else if (isctrl(scancode)) {
		ks ^= ctrl;
		return 1;
	} else if (isenter(scancode)) {
		submit_line();
		return 1;
	}
	return 0;
}

void keyboard_handler(struct regs *r) {
	u8 scancode = inb(KB_DATA);
	if (scancode & RELEASE) {
		check_key(scancode);
	} else {
		if (!check_key(scancode) && !shortcut(scancode)) {
			writek(letter(maj(scancode), layout), default_color, 1);
			add_character(*letter(maj(scancode), layout));
		}
	}
}

void keyboard_install() { irq_install_handler(1, keyboard_handler); }
void switch_layout(kbmap _layout) { layout = _layout; }
