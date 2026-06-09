#
# Create a compressed vmbeep image from the original vmbeep
#

targets		:= vmbeep vmbeep.bin vmbeep.bin.gz head.o misc.o piggy.o

LDFLAGS_vmbeep := -Ttext $(CONFIG_KERNEL_ZIMAGE_BASE_ADDRESS) -e startup_32

$(obj)/vmbeep: $(obj)/head.o $(obj)/misc.o $(obj)/piggy.o FORCE
	$(call if_changed,ld)
	@:

$(obj)/vmbeep.bin: vmbeep FORCE
	$(call if_changed,objcopy)

$(obj)/vmbeep.bin.gz: $(obj)/vmbeep.bin FORCE
	$(call if_changed,gzip)

LDFLAGS_piggy.o := -r --format binary --oformat elf32-am33lin -T

$(obj)/piggy.o: $(obj)/vmbeep.lds $(obj)/vmbeep.bin.gz FORCE
	$(call if_changed,ld)
