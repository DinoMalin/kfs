#pragma once

#include "types.h"

struct gdt_entry {
	u16 limit_low packed;
	u16 base_low packed;
	u8 base_middle packed;
	u8 access packed;
	u8 granularity packed;
	u8 base_high packed;
} packed;

struct gdt_ptr {
	u16 limit packed;
	u32 base packed;
} packed;

void gdt_install();

/* In 32 bits, we can use at max 4Go of RAM.
 *	We don't really want to use segmentation,
 *	as it is not really practical.
 *	What we do is giving every segment the
 *	whole RAM, letting them overlap
 *	themselves, so we use segmentation without
 *	using it.
 * */
#define LIMIT_MAX 0xFFFFFFFF

/* See https://wiki.osdev.org/Global_Descriptor_Table#Segment_Descriptor
 * for more informations on access and granularity bytes.
 */

#define NB_SEGMENTS 7
#define null_descriptor 0, 0, 0, 0
#define kernel_code 0, LIMIT_MAX, 0b10011011, 0b11001111
#define kernel_data 0, LIMIT_MAX, 0b10010011, 0b11001111
#define kernel_stack 0, LIMIT_MAX, 0b10010011, 0b11001111
#define user_code 0, LIMIT_MAX, 0b11111011, 0b11001111
#define user_data 0, LIMIT_MAX, 0b11110011, 0b11001111
#define user_stack 0, LIMIT_MAX, 0b11110011, 0b11001111
