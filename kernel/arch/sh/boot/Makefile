#
# arch/sh/boot/Makefile
#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#
# Copyright (C) 1999 Stuart Menefy
#

#
# Assign safe dummy values if these variables are not defined,
# in order to suppress error message.
#
CONFIG_PAGE_OFFSET	?= 0x80000000
CONFIG_MEMORY_START	?= 0x0c000000
CONFIG_BOOT_LINK_OFFSET	?= 0x00800000
CONFIG_ZERO_PAGE_OFFSET	?= 0x00001000
CONFIG_ENTRY_OFFSET	?= 0x00001000
CONFIG_PHYSICAL_START	?= $(CONFIG_MEMORY_START)

suffix-y := bin
suffix-$(CONFIG_KERNEL_GZIP)	:= gz
suffix-$(CONFIG_KERNEL_BZIP2)	:= bz2
suffix-$(CONFIG_KERNEL_LZMA)	:= lzma
suffix-$(CONFIG_KERNEL_XZ)	:= xz
suffix-$(CONFIG_KERNEL_LZO)	:= lzo

targets := zCalc vmbeep.srec romImage uImage uImage.srec uImage.gz \
	   uImage.bz2 uImage.lzma uImage.xz uImage.lzo uImage.bin
extra-y += vmbeep.bin vmbeep.bin.gz vmbeep.bin.bz2 vmbeep.bin.lzma \
	   vmbeep.bin.xz vmbeep.bin.lzo
subdir- := compressed romimage

$(obj)/zCalc: $(obj)/compressed/vmbeep FORCE
	$(call if_changed,objcopy)
	@echo '  Kernel: $@ is ready'

$(obj)/compressed/vmbeep: FORCE
	$(Q)$(MAKE) $(build)=$(obj)/compressed $@

$(obj)/romImage: $(obj)/romimage/vmbeep FORCE
	$(call if_changed,objcopy)
	@echo '  Kernel: $@ is ready'

$(obj)/romimage/vmbeep: $(obj)/zCalc FORCE
	$(Q)$(MAKE) $(build)=$(obj)/romimage $@

KERNEL_MEMORY	:= $(shell /bin/bash -c 'printf "0x%08x" \
		     $$[$(CONFIG_PHYSICAL_START) & 0x1fffffff]')

KERNEL_LOAD	:= $(shell /bin/bash -c 'printf "0x%08x" \
		     $$[$(CONFIG_PAGE_OFFSET)  + \
			$(KERNEL_MEMORY) + \
			$(CONFIG_ZERO_PAGE_OFFSET)]')

KERNEL_ENTRY	:= $(shell /bin/bash -c 'printf "0x%08x" \
		     $$[$(CONFIG_PAGE_OFFSET)  + \
			$(KERNEL_MEMORY) + \
			$(CONFIG_ZERO_PAGE_OFFSET) + $(CONFIG_ENTRY_OFFSET)]')

UIMAGE_LOADADDR = $(KERNEL_LOAD)
UIMAGE_ENTRYADDR = $(KERNEL_ENTRY)

$(obj)/vmbeep.bin: vmbeep FORCE
	$(call if_changed,objcopy)

$(obj)/vmbeep.bin.gz: $(obj)/vmbeep.bin FORCE
	$(call if_changed,gzip)

$(obj)/vmbeep.bin.bz2: $(obj)/vmbeep.bin FORCE
	$(call if_changed,bzip2)

$(obj)/vmbeep.bin.lzma: $(obj)/vmbeep.bin FORCE
	$(call if_changed,lzma)

$(obj)/vmbeep.bin.xz: $(obj)/vmbeep.bin FORCE
	$(call if_changed,xzkern)

$(obj)/vmbeep.bin.lzo: $(obj)/vmbeep.bin FORCE
	$(call if_changed,lzo)

$(obj)/uImage.bz2: $(obj)/vmbeep.bin.bz2
	$(call if_changed,uimage,bzip2)

$(obj)/uImage.gz: $(obj)/vmbeep.bin.gz
	$(call if_changed,uimage,gzip)

$(obj)/uImage.lzma: $(obj)/vmbeep.bin.lzma
	$(call if_changed,uimage,lzma)

$(obj)/uImage.xz: $(obj)/vmbeep.bin.xz
	$(call if_changed,uimage,xz)

$(obj)/uImage.lzo: $(obj)/vmbeep.bin.lzo
	$(call if_changed,uimage,lzo)

$(obj)/uImage.bin: $(obj)/vmbeep.bin
	$(call if_changed,uimage,none)

OBJCOPYFLAGS_vmbeep.srec := -I binary -O srec
$(obj)/vmbeep.srec: $(obj)/compressed/vmbeep
	$(call if_changed,objcopy)

OBJCOPYFLAGS_uImage.srec := -I binary -O srec
$(obj)/uImage.srec: $(obj)/uImage
	$(call if_changed,objcopy)

$(obj)/uImage: $(obj)/uImage.$(suffix-y)
	@ln -sf $(notdir $<) $@
	@echo '  Image $@ is ready'

export CONFIG_PAGE_OFFSET CONFIG_MEMORY_START CONFIG_BOOT_LINK_OFFSET \
       CONFIG_PHYSICAL_START CONFIG_ZERO_PAGE_OFFSET CONFIG_ENTRY_OFFSET \
       KERNEL_MEMORY suffix-y
