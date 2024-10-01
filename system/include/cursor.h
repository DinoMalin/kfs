#include "dinio.h"
#include "dinoint.h"

# define CURSOR_CMD	0x3D4
# define CURSOR_DATA	0x3D5

void move_cursor();
void disable_cursor();
void enable_cursor();
