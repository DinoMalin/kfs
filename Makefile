ISO=kernel.iso
GRUB_MOD=part_acorn part_amiga part_apple part_bsd part_dfly part_dvh part_gpt part_msdos part_plan part_sun part_sunpc normal multiboot
GRUB_RM=System efi boot/grub/x86_64-efi mach_kernel boot/grub/i386-efi boot/grub/themes efi.img

ROOTFS=rootfs

TCC_DIR=tinycc
CC=i386-tcc

all: tcc $(ISO) qemu

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

clean:
	rm $(ISO) -f

fclean: clean
	cd $(TCC_DIR) && \
	make clean && \
	cd ..

re: clean all
