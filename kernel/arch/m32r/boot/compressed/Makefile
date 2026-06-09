#
# beep/arch/m32r/boot/compressed/Makefile
#
# create a compressed vmbeep image from the original vmbeep
#

targets		:= vmbeep vmbeep.bin vmbeep.bin.gz vmbeep.bin.bz2 \
		   vmbeep.bin.lzma head.o misc.o piggy.o vmbeep.lds

OBJECTS = $(obj)/head.o $(obj)/misc.o

#
# IMAGE_OFFSET is the load offset of the compression loader
#
#IMAGE_OFFSET := $(shell printf "0x%08x" $$[$(CONFIG_MEMORY_START)+0x2000])
#IMAGE_OFFSET := $(shell printf "0x%08x" $$[$(CONFIG_MEMORY_START)+0x00400000])

LDFLAGS_vmbeep := -T

$(obj)/vmbeep: $(obj)/vmbeep.lds $(OBJECTS) $(obj)/piggy.o FORCE
	$(call if_changed,ld)
	@:

$(obj)/vmbeep.bin: vmbeep FORCE
	$(call if_changed,objcopy)

$(obj)/vmbeep.bin.gz: $(obj)/vmbeep.bin FORCE
	$(call if_changed,gzip)

$(obj)/vmbeep.bin.bz2: $(obj)/vmbeep.bin FORCE
	$(call if_changed,bzip2)

$(obj)/vmbeep.bin.lzma: $(obj)/vmbeep.bin FORCE
	$(call if_changed,lzma)

CFLAGS_misc.o += -fpic

ifdef CONFIG_MMU
LDFLAGS_piggy.o := -r --format binary --oformat elf32-m32r-beep -T
else
LDFLAGS_piggy.o := -r --format binary --oformat elf32-m32r -T
endif

OBJCOPYFLAGS += -R .empty_zero_page

suffix-$(CONFIG_KERNEL_GZIP)	= gz
suffix-$(CONFIG_KERNEL_BZIP2)	= bz2
suffix-$(CONFIG_KERNEL_LZMA)	= lzma

$(obj)/piggy.o: $(obj)/vmbeep.scr $(obj)/vmbeep.bin.$(suffix-y) FORCE
	$(call if_changed,ld)
