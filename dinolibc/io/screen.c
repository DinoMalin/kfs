#include "io.h"

void color_screen() {
	unsigned char *vmem = START_VMEM;

	while (vmem < END_VMEM) {
		color_cell(vmem);
		vmem += 2;
	}
}

void clear_screen() {
	unsigned char *vmem = START_VMEM;

	while (vmem < END_VMEM) {
		clear_cell(vmem);
		vmem += 2;
	}
}
