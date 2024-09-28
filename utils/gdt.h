#pragma once

# define packed __attribute__((packed))

struct gdt_entry
{
    unsigned short limit_low packed;
    unsigned short base_low packed;
    unsigned char base_middle packed;
    unsigned char access packed;
    unsigned char granularity packed;
    unsigned char base_high packed;
} packed;

struct gdt_ptr
{
    unsigned short limit packed;
    unsigned int base packed;
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
# define LIMIT_MAX 0xFFFFFFFF

/* See https://wiki.osdev.org/Global_Descriptor_Table#Segment_Descriptor
 * for more informations on access and granularity bytes.
*/

# define NB_SEGMENTS		5
# define null_descriptor	0, 0, 0, 0
# define kernel_code		0, LIMIT_MAX, 0b10011011, 0b11001111
# define kernel_data		0, LIMIT_MAX, 0b10010011, 0b11001111
# define user_code		0, LIMIT_MAX, 0b11111011, 0b11001111
# define user_data		0, LIMIT_MAX, 0b11110011, 0b11001111

