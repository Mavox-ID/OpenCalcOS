#
# Makefile for bootable kernel images
#

OBJCOPYFLAGS_vmbeep.bin := -O binary
$(obj)/vmbeep.bin: vmbeep FORCE
	$(call if_changed,objcopy)

$(obj)/dtbImage.%: vmbeep
	$(call if_changed,objcopy)
