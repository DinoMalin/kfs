#include "dinio.h"

void clear_screen() {
    unsigned char *vmem = START_VMEM;

    while (vmem < END_VMEM) {
	clear_cell(vmem)
	vmem += 2;
    }
}
