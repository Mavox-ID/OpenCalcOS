#
# beep/arch/x86/boot/compressed/Makefile
#
# create a compressed vmbeep image from the original vmbeep
#

targets := vmbeep.lds vmbeep vmbeep.bin vmbeep.bin.gz vmbeep.bin.bz2 vmbeep.bin.lzma vmbeep.bin.xz vmbeep.bin.lzo head_$(BITS).o misc.o string.o cmdline.o early_serial_console.o piggy.o

KBUILD_CFLAGS := -m$(BITS) -D__KERNEL__ $(BEEP_INCLUDE) -O2
KBUILD_CFLAGS += -fno-strict-aliasing -fPIC
KBUILD_CFLAGS += -DDISABLE_BRANCH_PROFILING
cflags-$(CONFIG_X86_32) := -march=i386
cflags-$(CONFIG_X86_64) := -mcmodel=small
KBUILD_CFLAGS += $(cflags-y)
KBUILD_CFLAGS += $(call cc-option,-ffreestanding)
KBUILD_CFLAGS += $(call cc-option,-fno-stack-protector)

KBUILD_AFLAGS  := $(KBUILD_CFLAGS) -D__ASSEMBLY__
GCOV_PROFILE := n

LDFLAGS := -m elf_$(UTS_MACHINE)
LDFLAGS_vmbeep := -T

hostprogs-y	:= mkpiggy
HOST_EXTRACFLAGS += -I$(srctree)/tools/include

VMBEEP_OBJS = $(obj)/vmbeep.lds $(obj)/head_$(BITS).o $(obj)/misc.o \
	$(obj)/string.o $(obj)/cmdline.o $(obj)/early_serial_console.o \
	$(obj)/piggy.o

$(obj)/eboot.o: KBUILD_CFLAGS += -fshort-wchar -mno-red-zone
$(obj)/efi_stub_$(BITS).o: KBUILD_CLFAGS += -fshort-wchar -mno-red-zone

ifeq ($(CONFIG_EFI_STUB), y)
	VMBEEP_OBJS += $(obj)/eboot.o $(obj)/efi_stub_$(BITS).o
endif

$(obj)/vmbeep: $(VMBEEP_OBJS) FORCE
	$(call if_changed,ld)
	@:

OBJCOPYFLAGS_vmbeep.bin :=  -R .comment -S
$(obj)/vmbeep.bin: vmbeep FORCE
	$(call if_changed,objcopy)

targets += vmbeep.bin.all vmbeep.relocs

CMD_RELOCS = arch/x86/tools/relocs
quiet_cmd_relocs = RELOCS  $@
      cmd_relocs = $(CMD_RELOCS) $< > $@;$(CMD_RELOCS) --abs-relocs $<
$(obj)/vmbeep.relocs: vmbeep FORCE
	$(call if_changed,relocs)

vmbeep.bin.all-y := $(obj)/vmbeep.bin
vmbeep.bin.all-$(CONFIG_X86_NEED_RELOCS) += $(obj)/vmbeep.relocs

$(obj)/vmbeep.bin.gz: $(vmbeep.bin.all-y) FORCE
	$(call if_changed,gzip)
$(obj)/vmbeep.bin.bz2: $(vmbeep.bin.all-y) FORCE
	$(call if_changed,bzip2)
$(obj)/vmbeep.bin.lzma: $(vmbeep.bin.all-y) FORCE
	$(call if_changed,lzma)
$(obj)/vmbeep.bin.xz: $(vmbeep.bin.all-y) FORCE
	$(call if_changed,xzkern)
$(obj)/vmbeep.bin.lzo: $(vmbeep.bin.all-y) FORCE
	$(call if_changed,lzo)

suffix-$(CONFIG_KERNEL_GZIP)	:= gz
suffix-$(CONFIG_KERNEL_BZIP2)	:= bz2
suffix-$(CONFIG_KERNEL_LZMA)	:= lzma
suffix-$(CONFIG_KERNEL_XZ)	:= xz
suffix-$(CONFIG_KERNEL_LZO) 	:= lzo

quiet_cmd_mkpiggy = MKPIGGY $@
      cmd_mkpiggy = $(obj)/mkpiggy $< > $@ || ( rm -f $@ ; false )

targets += piggy.S
$(obj)/piggy.S: $(obj)/vmbeep.bin.$(suffix-y) $(obj)/mkpiggy FORCE
	$(call if_changed,mkpiggy)
