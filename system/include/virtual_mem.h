#pragma once

// LIN*COL*2
#define VIDEO_AREA						4000

#define resolve_page_table(address)		(address / 0x400000)
#define resolve_table_offset(address)	(address % 0x400000)
#define present(table)					(table & 1)

/* Identity map : mapping a virtual address to the same physical
 * address. Useful for address like the video memory.
**/
#define IDENTITY_MAP(addr, len)			map_zone(addr, addr, len)
void init_page_directory();

