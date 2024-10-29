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
DINOLIB_SRC		= $(shell find $(DINOLIB_DIR) -name "*.c")
DINOLIB_OBJ		= $(DINOLIB_SRC:%.c=$(OBJ_DIR)/%.o)

DINOSH_DIR		= shell
DINOSH_SRC		= $(wildcard $(DINOSH_DIR)/*.c)
DINOSH_OBJ		= $(DINOSH_SRC:%.c=$(OBJ_DIR)/%.o)

theme=dinosaur
PS1=DinOS>

TCC_GIT	= https://github.com/TinyCC/tinycc
TCC_DIR	= tinycc
LIBTCC	= ./$(TCC_DIR)/i386-libtcc1.a

CC			= $(TCC_DIR)/i386-tcc
CFLAGS		= -nostdlib -fno-builtin -fno-stack-protector \
			  -I $(DINOLIB_LIB_DIR) -I $(SYSTEM_INC_DIR) -I $(DINOSH_DIR) \
			  '-Ddefault_theme="$(theme)"' '-DPS1="$(PS1) "' -g \
			  -Werror
LDFLAGS		= -m elf_i386 

SHELL		= bash

define legend
	@echo -en "\e[1;38;2;163;255;149m$(1) \e[0m"
	@echo $(2)
endef

define legend_forget
	@echo -en "\e[1;38;2;163;255;149m$(1) \e[0m"
	@echo -en "$(2)"
	@echo -en "                              \r"
endef

define bad_legend
	@echo -en "\e[1;38;2;255;149;149m$(1) \e[0m"
	@echo $(2)
endef

all: $(CC) $(KERNEL)
	$(call legend,"Creating",$(ISO))
	@grub-mkrescue --directory=$(GRUB_DIR) -o $(ISO) $(ROOTFS) "--install-modules=$(GRUB_MOD)" -- -rm_r $(GRUB_RM) --  2>/dev/null
	$(call legend,"Launching VM...",)
	@qemu-system-i386 -cdrom $(ISO) -serial stdio

.ONESHELL:
$(CC):
	$(call legend,"Compiling TCC...",)
	@git clone $(TCC_GIT) --quiet
	@cd $(TCC_DIR)
	@./configure >/dev/null
	@make cross-i386 --quiet 2>/dev/null
	@cd ..

$(KERNEL): $(START_OBJ) $(KMAIN_OBJ) $(DINOLIB_OBJ) $(SYSTEM_OBJ) $(DINOSH_OBJ)
	$(call legend,"Linking",$@)
	@$(LD) $(LDFLAGS) --script=$(LINKER) $^ $(LIBTCC) -o $(KERNEL)

$(OBJ_DIR)/%.o: %.s
	$(call legend_forget,"Compiling",$<)
	@mkdir -p $(dir $@)
	@nasm $< -f elf -o $@

$(OBJ_DIR)/%.o: %.c
	$(call legend_forget,"Compiling",$<)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS)  -c $< -o $@

clean:
	$(call bad_legend,"Cleaning",)
	@$(RM) $(ISO)
	@$(RM) $(KMAIN_OBJ) $(START_OBJ)
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(RM) -r $(TCC_DIR)

re: clean all

