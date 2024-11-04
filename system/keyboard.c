#include "keyboard.h"

u8 kbus[256] = {
	0,		  ESCAPE,	'1',	   '2',		  '3',		   '4',
	'5',	  '6',		'7',	   '8',		  '9',		   '0',
	'-',	  '=',		BACKSPACE, TAB,		  'q',		   'w',
	'e',	  'r',		't',	   'y',		  'u',		   'i',
	'o',	  'p',		'[',	   ']',		  ENTER,	   CTRL,
	'a',	  's',		'd',	   'f',		  'g',		   'h',
	'j',	  'k',		'l',	   ';',		  '\'',		   '`',
	LSHIFT,	  '\\',		'z',	   'x',		  'c',		   'v',
	'b',	  'n',		'm',	   ',',		  '.',		   '/',
	RSHIFT,	  '*',		ALT,	   SPACE,	  CAPS_LOCK,   F1,
	F2,		  F3,		F4,		   F5,		  F6,		   F7,
	F8,		  F9,		F10,	   NUM_LOCK,  SCROLL_LOCK, HOME,
	UP,		  PAGE_UP,	'-',	   LEFT,	  UNMAPPED,	   RIGHT,
	'+',	  END,		DOWN,	   PAGE_DOWN, INSERT,	   DELETE,
	UNMAPPED, UNMAPPED, UNMAPPED,  F11,		  F12,		   unmapped_end,
	0,		  ESCAPE,	'1',	   '2',		  '3',		   '4',
	'5',	  '6',		'7',	   '8',		  '9',		   '0',
	'_',	  '=',		BACKSPACE, TAB,		  'Q',		   'W',
	'E',	  'R',		'T',	   'Y',		  'U',		   'I',
	'O',	  'P',		'[',	   ']',		  ENTER,	   CTRL,
	'A',	  'S',		'D',	   'F',		  'G',		   'H',
	'J',	  'K',		'L',	   ';',		  '\'',		   '`',
	LSHIFT,	  '\\',		'Z',	   'X',		  'C',		   'V',
	'B',	  'N',		'M',	   ',',		  '.',		   '/',
	RSHIFT,	  '*',		ALT,	   SPACE,	  CAPS_LOCK,   F1,
	F2,		  F3,		F4,		   F5,		  F6,		   F7,
	F8,		  F9,		F10,	   NUM_LOCK,  SCROLL_LOCK, HOME,
	UP,		  PAGE_UP,	'-',	   LEFT,	  UNMAPPED,	   RIGHT,
	'+',	  END,		DOWN,	   PAGE_DOWN, INSERT,	   DELETE,
	UNMAPPED, UNMAPPED, UNMAPPED,  F11,		  F12,		   UNMAPPED,
};

key_status ks = 0;
int enter = 0;

int shortcut(u8 scancode) {
	if (CTRL_SHORT('a')) {
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
			writek(&kbus[maj(scancode)], default_color, 1);
			add_character(kbus[maj(scancode)]);
		}
	}
}

void keyboard_install() { irq_install_handler(1, keyboard_handler); }
