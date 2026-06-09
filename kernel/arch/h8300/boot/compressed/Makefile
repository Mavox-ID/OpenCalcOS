#
# beep/arch/sh/boot/compressed/Makefile
#
# create a compressed vmbeep image from the original vmbeep
#

targets		:= vmbeep vmbeep.bin vmbeep.bin.gz head.o misc.o piggy.o
asflags-y	:= -traditional

OBJECTS = $(obj)/head.o $(obj)/misc.o

#
# IMAGE_OFFSET is the load offset of the compression loader
# Assign dummy values if these 2 variables are not defined,
# in order to suppress error message.
#
CONFIG_MEMORY_START     ?= 0x00400000
CONFIG_BOOT_LINK_OFFSET ?= 0x00140000
IMAGE_OFFSET := $(shell printf "0x%08x" $$[$(CONFIG_MEMORY_START)+$(CONFIG_BOOT_LINK_OFFSET)])

LDFLAGS_vmbeep := -Ttext $(IMAGE_OFFSET) -estartup $(obj)/vmbeep.lds

$(obj)/vmbeep: $(OBJECTS) $(obj)/piggy.o FORCE
	$(call if_changed,ld)
	@:

$(obj)/vmbeep.bin: vmbeep FORCE
	$(call if_changed,objcopy)

$(obj)/vmbeep.bin.gz: $(obj)/vmbeep.bin FORCE
	$(call if_changed,gzip)

LDFLAGS_piggy.o := -r --format binary --oformat elf32-h8300 -T
OBJCOPYFLAGS := -O binary

$(obj)/piggy.o: $(obj)/vmbeep.scr $(obj)/vmbeep.bin.gz FORCE
	$(call if_changed,ld)
