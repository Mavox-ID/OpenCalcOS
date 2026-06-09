#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#

ifeq ($(BIG_ENDIAN),1)
OBJCOPY_ARGS 	:= -O elf32-xtensa-be
else
OBJCOPY_ARGS 	:= -O elf32-xtensa-le
endif

LD_ARGS	= -T $(srctree)/$(obj)/boot.ld

boot-y	:= bootstrap.o

OBJS	:= $(addprefix $(obj)/,$(boot-y))
LIBS	:= arch/xtensa/boot/lib/lib.a arch/xtensa/lib/lib.a

LIBGCC := $(shell $(CC) $(KBUILD_CFLAGS) -print-libgcc-file-name)

$(obj)/zCalc.o: vmbeep.bin.gz $(OBJS)
	$(Q)$(OBJCOPY) $(OBJCOPY_ARGS) -R .comment \
		--add-section image=vmbeep.bin.gz \
		--set-section-flags image=contents,alloc,load,load,data \
		$(OBJS) $@

$(obj)/zCalc.elf: $(obj)/zCalc.o $(LIBS)
	$(Q)$(LD) $(LD_ARGS) -o $@ $^ -L/xtensa-elf/lib $(LIBGCC)

$(obj)/../zCalc.redboot: $(obj)/zCalc.elf
	$(Q)$(OBJCOPY) -S -O binary $< $@
	$(Q)$(kecho) '  Kernel: $@ is ready'

zCalc: $(obj)/../zCalc.redboot
