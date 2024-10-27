ISO			= kernel.iso
GRUB_MOD	= part_acorn part_amiga part_apple part_bsd \
			  part_dfly part_dvh part_gpt part_msdos \
			  part_plan part_sun part_sunpc normal multiboot
GRUB_RM		= System efi boot/grub/x86_64-efi mach_kernel \
			  boot/grub/i386-efi boot/grub/themes efi.img \
			  boot/grub/locale
GRUB_DIR	= i386-pc

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
SYSTEM_SRC_C	= $(wildcard $(SYSTEM_DIR)/*.c)
SYSTEM_SRC_S	= $(wildcard $(SYSTEM_DIR)/*.s)
SYSTEM_OBJ		= $(SYSTEM_SRC_C:%.c=$(OBJ_DIR)/%.o) \
				  $(SYSTEM_SRC_S:%.s=$(OBJ_DIR)/%.o)
SYSTEM_INC_DIR	= $(SYSTEM_DIR)/include

DINOLIB_DIR		= dinolibc
DINOLIB_LIB_DIR	= $(DINOLIB_DIR)/include
DINOLIB_SRC		= $(wildcard $(DINOLIB_DIR)/**/*.c)
DINOLIB_OBJ		= $(DINOLIB_SRC:%.c=$(OBJ_DIR)/%.o)

DINOSH_DIR		= shell
DINOSH_SRC		= $(wildcard $(DINOSH_DIR)/*.c)
DINOSH_OBJ		= $(DINOSH_SRC:%.c=$(OBJ_DIR)/%.o)

theme=dinosaur
PS1=DinOS>

TCC_GIT	= https://github.com/TinyCC/tinycc
TCC_DIR	= tinycc

CC			= ./$(TCC_DIR)/i386-tcc
CFLAGS		= -nostdlib -fno-builtin -fno-stack-protector \
			  -I $(DINOLIB_LIB_DIR) -I $(SYSTEM_INC_DIR) -I $(DINOSH_DIR) \
			  '-Ddefault_theme="$(theme)"' '-DPS1="$(PS1) "' -g
LDFLAGS		= -m elf_i386 


all: $(CC) $(KERNEL)
	grub-mkrescue --directory=$(GRUB_DIR) -o $(ISO) $(ROOTFS) "--install-modules=$(GRUB_MOD)" -- -rm_r $(GRUB_RM) -- 
	qemu-system-i386 -cdrom $(ISO) -serial stdio

.ONESHELL:
$(CC):
	git clone $(TCC_GIT)
	cd $(TCC_DIR) 
	./configure
	make cross-i386
	cd ..

$(KERNEL): $(START_OBJ) $(KMAIN_OBJ) $(DINOLIB_OBJ) $(SYSTEM_OBJ) $(DINOSH_OBJ)
	$(LD) $(LDFLAGS) --script=$(LINKER) $^ -o $(KERNEL)

$(OBJ_DIR)/%.o: %.s
	mkdir -p $(dir $@)
	nasm $< -f elf -o $@

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	$(RM) $(ISO)
	$(RM) $(KMAIN_OBJ) $(START_OBJ)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	rm -rf $(TCC_DIR)

re: clean all
