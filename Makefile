ISO			= kernel.iso
GRUB_MOD	= part_acorn part_amiga part_apple part_bsd part_dfly part_dvh part_gpt part_msdos part_plan part_sun part_sunpc normal multiboot
GRUB_RM		= System efi boot/grub/x86_64-efi mach_kernel boot/grub/i386-efi boot/grub/themes efi.img

ROOTFS		= rootfs
KERNEL_DIR	= kernel

OBJ_DIR		= obj

START		= $(KERNEL_DIR)/start.s
START_OBJ	= $(OBJ_DIR)/$(KERNEL_DIR)/start.o
KMAIN		= $(KERNEL_DIR)/kernel.c
KMAIN_OBJ	= $(OBJ_DIR)/$(KERNEL_DIR)/kernel.o
LINKER		= $(KERNEL_DIR)/linker.ld
KERNEL		= $(ROOTFS)/boot/kernel.elf

SYSTEM_DIR		= system
SYSTEM_C		= gdt idt irq timer keyboard
SYSTEM_S		= interrupts
SYSTEM_SRC		= $(addprefix $(SYSTEM_DIR)/, $(addsuffix .c, $(SYSTEM_C))) \
				  $(addprefix $(SYSTEM_DIR)/, $(addsuffix .s, $(SYSTEM_S)))
SYSTEM_OBJ		= $(addprefix $(OBJ_DIR)/, $(addprefix $(SYSTEM_DIR)/, $(addsuffix .o, $(SYSTEM_C)))) \
				  $(addprefix $(OBJ_DIR)/, $(addprefix $(SYSTEM_DIR)/, $(addsuffix .o, $(SYSTEM_S))))
SYSTEM_INC_DIR	= $(SYSTEM_DIR)/include

DINOLIB_DIR		= dinolibc
DINOLIB_LIB_DIR	= $(DINOLIB_DIR)/headers
DINOLIB			= dinostring/strlen dinostring/strncmp dinostring/memset \
				  dinio/writek dinio/printk dinio/io dinio/print_stack
DINOLIB_SRC		= $(addprefix $(DINOLIB_DIR)/, $(addsuffix .c, $(DINOLIB)))
DINOLIB_OBJ		= $(addprefix $(OBJ_DIR)/, $(addprefix $(DINOLIB_DIR)/, $(addsuffix .o, $(DINOLIB))))

TCC_DIR	= tinycc
CC		= ./$(TCC_DIR)/i386-tcc
CFLAGS	= -nostdlib -fno-builtin -fno-stack-protector -I $(DINOLIB_LIB_DIR) -I $(SYSTEM_INC_DIR)

BG=WHITE
FG=RED

all: tcc $(KERNEL) $(ISO) qemu

.ONESHELL:
tcc:
	cd $(TCC_DIR) 
	./configure
	make cross-i386
	cd ..

$(ISO):
	grub-mkrescue -o $(ISO) $(ROOTFS) "--install-modules=$(GRUB_MOD)" -- -rm_r $(GRUB_RM) -- 

qemu:
	qemu-system-i386 -cdrom $(ISO) -serial stdio

$(KERNEL): $(START_OBJ) $(KMAIN_OBJ) $(DINOLIB_OBJ) $(SYSTEM_OBJ)
	$(LD) -m elf_i386 --script=$(LINKER) $(START_OBJ) $(KMAIN_OBJ) $(DINOLIB_OBJ) $(SYSTEM_OBJ) -o $(KERNEL)

$(OBJ_DIR)/%.o: %.s
	mkdir -p $(dir $@)
	nasm $< -f elf -o $@

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -DMAIN_COLOR_FG=$(FG) -DMAIN_COLOR_BG=$(BG) -c $< -o $@

clean:
	rm $(ISO) -f
	rm $(KMAIN_OBJ) $(START_OBJ) -f
	rm -rf $(OBJ_DIR)

fclean: clean
	cd $(TCC_DIR) && \
	make clean && \
	cd ..

re: clean all
