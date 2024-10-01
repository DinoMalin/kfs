#include "keyboard.h"

unsigned char kbus[128] = {
    0,  ESCAPE, '1', '2', '3', '4', '5', '6', '7', '8',	'9', '0', '-', '=', BACKSPACE,
    TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', ENTER,	CTRL,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    LSHIFT, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   RSHIFT, '*',
    ALT, SPACE, CAPS_LOCK, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, NUM_LOCK,
    SCROLL_LOCK, HOME, UP, PAGE_UP, '-', LEFT, UNMAPPED, RIGHT, '+', END, DOWN,
    PAGE_DOWN, INSERT, DELETE, UNMAPPED, UNMAPPED, UNMAPPED, F11, F12, UNMAPPED
};

key_status	ks = 0;
lock_status	ls = 0;

void keyboard_handler(struct regs *r) {
    unsigned char scancode = inb(KB_DATA);
    if (scancode & RELEASE) {
        // TO DO : RELEASE
    } else {
        writek(&kbus[scancode], DEFAULT, 1);
    }
}

void keyboard_install() {
   irq_install_handler(1, keyboard_handler); 
}
