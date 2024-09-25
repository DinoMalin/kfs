#include "dinio.h"
#include "dinostring.h"

unsigned char *video_memory         = (unsigned char *)0xB8000;
unsigned char *last_written_addr    = (unsigned char *)0xB8000;

void kmain() {
    printk("dinomalin dinomalin : %dbbb  %% aa a %s %c", 9, "kawaiine", 'i');
    printk("DinoMalin Was Here");
}
