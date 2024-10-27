ISO			= kernel.iso
GRUB_MOD	= part_acorn part_amiga part_apple part_bsd part_dfly part_dvh part_gpt part_msdos part_plan part_sun part_sunpc normal multiboot
GRUB_RM		= System efi boot/grub/x86_64-efi mach_kernel boot/grub/i386-efi boot/grub/themes efi.img boot/grub/locale
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
SYSTEM_C		= gdt idt irq timer keyboard cursor workspace physical_mem virtual_mem
SYSTEM_S		= interrupts paging
SYSTEM_SRC		= $(addprefix $(SYSTEM_DIR)/, $(addsuffix .c, $(SYSTEM_C))) \
				  $(addprefix $(SYSTEM_DIR)/, $(addsuffix .s, $(SYSTEM_S)))
SYSTEM_OBJ		= $(addprefix $(OBJ_DIR)/, $(addprefix $(SYSTEM_DIR)/, $(addsuffix .o, $(SYSTEM_C)))) \
				  $(addprefix $(OBJ_DIR)/, $(addprefix $(SYSTEM_DIR)/, $(addsuffix .o, $(SYSTEM_S))))
SYSTEM_INC_DIR	= $(SYSTEM_DIR)/include

DINOLIB_DIR		= dinolibc
DINOLIB_LIB_DIR	= $(DINOLIB_DIR)/include
DINOLIB			= dinostring/strlen dinostring/strncmp dinostring/memset \
				  dinostring/isalpha dinostring/isdigit dinostring/atoi \
				  dinostring/address dinostring/strchr \
				  dinio/writek dinio/printk dinio/io dinio/memory dinio/screen
DINOLIB_SRC		= $(addprefix $(DINOLIB_DIR)/, $(addsuffix .c, $(DINOLIB)))
DINOLIB_OBJ		= $(addprefix $(OBJ_DIR)/, $(addprefix $(DINOLIB_DIR)/, $(addsuffix .o, $(DINOLIB))))

DINOSH_DIR		= shell
DINOSH			= shell utils commands
DINOSH_SRC		= $(addprefix $(DINOSH_DIR)/, $(addsuffix .c, $(DINOSH)))
DINOSH_OBJ		= $(addprefix $(OBJ_DIR)/, $(addprefix $(DINOSH_DIR)/, $(addsuffix .o, $(DINOSH))))

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
