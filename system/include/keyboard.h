#pragma once
# include "dinio.h"
# include "irq.h"

typedef enum {
    ctrl    = 1 << 0,
    alt	    = 1 << 1,
    shift   = 1 << 2
} key_status;

void keyboard_install();

# define KB_CMD     0x64
# define KB_DATA    0x60

# define RELEASE    0b10000000
# define KB_READY   0b00000010

# define LSHIFT_SC_PRESS    0x2A
# define RSHIFT_SC_PRESS    0x36
# define LSHIFT_SC_RELEASE  0xAA
# define RSHIFT_SC_RELEASE  0xB6

# define isshift(x) (x == LSHIFT_SC_PRESS || x == RSHIFT_SC_PRESS || x == LSHIFT_SC_RELEASE || x == RSHIFT_SC_RELEASE)

# define maj(scancode) (ks & shift ? scancode + 128 : scancode)
# define unmapped_end	0, 0, 0, 0, \
			0, 0, 0, 0, \
			0, 0, 0, 0, \
			0, 0, 0, 0, \
			0, 0, 0, 0, \
			0, 0, 0, 0, \
			0, 0, 0, 0, \
			0, 0, 0, 0, \
			0, 0, 0, 0, \
			0, 0, 0 \


# define ESCAPE          27
# define BACKSPACE      '\b'
# define TAB            '\t'
# define ENTER          '\n'
# define CTRL           0
# define LSHIFT         0
# define RSHIFT         0
# define ALT            0
# define SPACE          ' '
# define CAPS_LOCK      0
# define F1             0
# define F2             0
# define F3             0
# define F4             0
# define F5             0
# define F6             0
# define F7             0
# define F8             0
# define F9             0
# define F10            0
# define F11            0
# define F12            0
# define NUM_LOCK       0
# define SCROLL_LOCK    0
# define HOME           0
# define UP             0
# define LEFT           0
# define RIGHT          0
# define DOWN           0
# define PAGE_UP        0
# define PAGE_DOWN      0
# define END            0
# define INSERT         0
# define DELETE         0
# define UNMAPPED       0
