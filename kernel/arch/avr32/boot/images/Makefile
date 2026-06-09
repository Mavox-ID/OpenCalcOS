#
# Copyright (C) 2004-2006 Atmel Corporation
#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#

extra-y		:= vmbeep.bin vmbeep.gz

OBJCOPYFLAGS_vmbeep.bin := -O binary -R .note.gnu.build-id
$(obj)/vmbeep.bin: vmbeep FORCE
	$(call if_changed,objcopy)

$(obj)/vmbeep.gz: $(obj)/vmbeep.bin FORCE
	$(call if_changed,gzip)

UIMAGE_LOADADDR = $(CONFIG_LOAD_ADDRESS)
UIMAGE_ENTRYADDR = $(CONFIG_ENTRY_ADDRESS)
UIMAGE_COMPRESSION = gzip

targets += uImage uImage.srec
$(obj)/uImage: $(obj)/vmbeep.gz
	$(call if_changed,uimage)
	@echo '  Image $@ is ready'

OBJCOPYFLAGS_uImage.srec := -I binary -O srec
$(obj)/uImage.srec: $(obj)/uImage
	$(call if_changed,objcopy)

OBJCOPYFLAGS_vmbeep.elf := --change-section-lma .text-0x80000000 \
			    --change-section-lma __ex_table-0x80000000 \
			    --change-section-lma .rodata-0x80000000 \
			    --change-section-lma .data-0x80000000 \
			    --change-section-lma .init-0x80000000 \
			    --change-section-lma .bss-0x80000000 \
			    --change-section-lma __param-0x80000000 \
			    --change-section-lma __ksymtab-0x80000000 \
			    --change-section-lma __ksymtab_gpl-0x80000000 \
			    --change-section-lma __kcrctab-0x80000000 \
			    --change-section-lma __kcrctab_gpl-0x80000000 \
			    --change-section-lma __ksymtab_strings-0x80000000 \
			    --set-start 0xa0000000
$(obj)/vmbeep.elf: vmbeep FORCE
	$(call if_changed,objcopy)

quiet_cmd_sfdwarf = SFDWARF $@
      cmd_sfdwarf = sfdwarf $< TO $@ GNUAVR IW $(SFDWARF_FLAGS) > $(obj)/sfdwarf.log

$(obj)/vmbeep.cso: $(obj)/vmbeep.elf FORCE
	$(call if_changed,sfdwarf)

install: $(BOOTIMAGE)
	sh $(srctree)/install-kernel.sh $<

# Generated files to be removed upon make clean
clean-files	:= vmbeep.elf vmbeep.bin vmbeep.gz uImage uImage.srec
