#
# arch/blackfin/boot/Makefile
#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#

targets := vmImage vmImage.bin vmImage.bz2 vmImage.gz vmImage.lzma vmImage.lzo vmImage.xip
extra-y += vmbeep.bin vmbeep.bin.gz vmbeep.bin.bz2 vmbeep.bin.lzma vmbeep.bin.lzo vmbeep.bin.xip

ifeq ($(CONFIG_RAMKERNEL),y)
UIMAGE_LOADADDR = $(CONFIG_BOOT_LOAD)
else # CONFIG_ROMKERNEL must be set
UIMAGE_LOADADDR = $(CONFIG_ROM_BASE)
endif
UIMAGE_ENTRYADDR = $(shell $(NM) vmbeep | awk '$$NF == "__start" {print $$1}')
UIMAGE_NAME = '$(CPU_REV)-$(KERNELRELEASE)'
UIMAGE_OPTS-$(CONFIG_ROMKERNEL) += -x

$(obj)/vmbeep.bin: vmbeep FORCE
	$(call if_changed,objcopy)

$(obj)/vmbeep.bin.gz: $(obj)/vmbeep.bin FORCE
	$(call if_changed,gzip)

$(obj)/vmbeep.bin.bz2: $(obj)/vmbeep.bin FORCE
	$(call if_changed,bzip2)

$(obj)/vmbeep.bin.lzma: $(obj)/vmbeep.bin FORCE
	$(call if_changed,lzma)

$(obj)/vmbeep.bin.lzo: $(obj)/vmbeep.bin FORCE
	$(call if_changed,lzo)

# The mkimage tool wants 64bytes prepended to the image
quiet_cmd_mk_bin_xip = BIN     $@
      cmd_mk_bin_xip = ( printf '%64s' | tr ' ' '\377' ; cat $< ) > $@
$(obj)/vmbeep.bin.xip: $(obj)/vmbeep.bin FORCE
	$(call if_changed,mk_bin_xip)

$(obj)/vmImage.bin: $(obj)/vmbeep.bin
	$(call if_changed,uimage,none)

$(obj)/vmImage.bz2: $(obj)/vmbeep.bin.bz2
	$(call if_changed,uimage,bzip2)

$(obj)/vmImage.gz: $(obj)/vmbeep.bin.gz
	$(call if_changed,uimage,gzip)

$(obj)/vmImage.lzma: $(obj)/vmbeep.bin.lzma
	$(call if_changed,uimage,lzma)

$(obj)/vmImage.lzo: $(obj)/vmbeep.bin.lzo
	$(call if_changed,uimage,lzo)

$(obj)/vmImage.xip: $(obj)/vmbeep.bin.xip
	$(call if_changed,uimage,none)

suffix-y                      := bin
suffix-$(CONFIG_KERNEL_GZIP)  := gz
suffix-$(CONFIG_KERNEL_BZIP2) := bz2
suffix-$(CONFIG_KERNEL_LZMA)  := lzma
suffix-$(CONFIG_KERNEL_LZO)   := lzo
suffix-$(CONFIG_ROMKERNEL)    := xip

$(obj)/vmImage: $(obj)/vmImage.$(suffix-y)
	@ln -sf $(notdir $<) $@

install:
	sh $(srctree)/$(src)/install.sh $(KERNELRELEASE) $(BOOTIMAGE) System.map "$(INSTALL_PATH)"
