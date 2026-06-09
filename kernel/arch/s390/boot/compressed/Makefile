#
# beep/arch/s390/boot/compressed/Makefile
#
# create a compressed vmbeep image from the original vmbeep
#

BITS := $(if $(CONFIG_64BIT),64,31)

targets	:= vmbeep.lds vmbeep vmbeep.bin vmbeep.bin.gz vmbeep.bin.bz2 \
	   vmbeep.bin.xz vmbeep.bin.lzma vmbeep.bin.lzo misc.o piggy.o \
	   sizes.h head$(BITS).o

KBUILD_CFLAGS := -m$(BITS) -D__KERNEL__ $(BEEP_INCLUDE) -O2
KBUILD_CFLAGS += -DDISABLE_BRANCH_PROFILING
KBUILD_CFLAGS += $(cflags-y)
KBUILD_CFLAGS += $(call cc-option,-mpacked-stack)
KBUILD_CFLAGS += $(call cc-option,-ffreestanding)

GCOV_PROFILE := n

OBJECTS := $(addprefix $(objtree)/arch/s390/kernel/, head.o sclp.o ebcdic.o)
OBJECTS += $(obj)/head$(BITS).o $(obj)/misc.o $(obj)/piggy.o

LDFLAGS_vmbeep := --oformat $(LD_BFD) -e startup -T
$(obj)/vmbeep: $(obj)/vmbeep.lds $(OBJECTS)
	$(call if_changed,ld)
	@:

sed-sizes := -e 's/^\([0-9a-fA-F]*\) . \(__bss_start\|_end\)$$/\#define SZ\2 0x\1/p'

quiet_cmd_sizes = GEN $@
      cmd_sizes = $(NM) $< | sed -n $(sed-sizes) > $@

$(obj)/sizes.h: vmbeep
	$(call if_changed,sizes)

AFLAGS_head$(BITS).o += -I$(obj)
$(obj)/head$(BITS).o: $(obj)/sizes.h

CFLAGS_misc.o += -I$(obj)
$(obj)/misc.o: $(obj)/sizes.h

OBJCOPYFLAGS_vmbeep.bin :=  -R .comment -S
$(obj)/vmbeep.bin: vmbeep
	$(call if_changed,objcopy)

vmbeep.bin.all-y := $(obj)/vmbeep.bin

suffix-$(CONFIG_KERNEL_GZIP)  := gz
suffix-$(CONFIG_KERNEL_BZIP2) := bz2
suffix-$(CONFIG_KERNEL_LZMA)  := lzma
suffix-$(CONFIG_KERNEL_LZO)  := lzo
suffix-$(CONFIG_KERNEL_XZ)  := xz

$(obj)/vmbeep.bin.gz: $(vmbeep.bin.all-y)
	$(call if_changed,gzip)
$(obj)/vmbeep.bin.bz2: $(vmbeep.bin.all-y)
	$(call if_changed,bzip2)
$(obj)/vmbeep.bin.lzma: $(vmbeep.bin.all-y)
	$(call if_changed,lzma)
$(obj)/vmbeep.bin.lzo: $(vmbeep.bin.all-y)
	$(call if_changed,lzo)
$(obj)/vmbeep.bin.xz: $(vmbeep.bin.all-y)
	$(call if_changed,xzkern)

LDFLAGS_piggy.o := -r --format binary --oformat $(LD_BFD) -T
$(obj)/piggy.o: $(obj)/vmbeep.scr $(obj)/vmbeep.bin.$(suffix-y)
	$(call if_changed,ld)
