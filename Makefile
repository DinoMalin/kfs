ISO			= kernel.iso
GRUB_MOD	= part_acorn part_amiga part_apple part_bsd part_dfly part_dvh part_gpt part_msdos part_plan part_sun part_sunpc normal multiboot
GRUB_RM		= System efi boot/grub/x86_64-efi mach_kernel boot/grub/i386-efi boot/grub/themes efi.img

ROOTFS		= rootfs
KERNEL_DIR	= kernel

TCC_DIR	= tinycc
CC		= ./$(TCC_DIR)/i386-tcc

START		= $(KERNEL_DIR)/start32.asm
START_OBJ	= $(KERNEL_DIR)/start32.o
KMAIN		= $(KERNEL_DIR)/kernel.c
KMAIN_OBJ	= $(KERNEL_DIR)/kernel.o
KERNEL		= $(ROOTFS)/boot/kernel.elf

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
	qemu-system-i386 -cdrom $(ISO)

$(KERNEL): $(START_OBJ) $(KMAIN_OBJ)
	$(CC) -nostdlib -Wl,-Ttext,0x100000 $(START_OBJ) $(KMAIN_OBJ) -o $(KERNEL)

.ONESHELL:
$(START_OBJ):
	nasm $(START) -f elf

.ONESHELL:
$(KMAIN_OBJ):
	$(CC) -c $(KMAIN) -o $(KMAIN_OBJ)

clean:
	rm $(ISO) -f
	rm $(KMAIN_OBJ) $(START_OBJ) -f

fclean: clean
	cd $(TCC_DIR) && \
	make clean && \
	cd ..

re: clean all
