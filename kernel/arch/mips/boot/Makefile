#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#
# Copyright (C) 1995, 1998, 2001, 2002 by Ralf Baechle
# Copyright (C) 2004  Maciej W. Rozycki
#

#
# Some DECstations need all possible sections of an ECOFF executable
#
ifdef CONFIG_MACH_DECSTATION
  e2eflag := -a
endif

#
# Drop some uninteresting sections in the kernel.
# This is only relevant for ELF kernels but doesn't hurt a.out
#
drop-sections := .reginfo .mdebug .comment .note .pdr .options .MIPS.options
strip-flags   := $(addprefix --remove-section=,$(drop-sections))

hostprogs-y := elf2ecoff

targets := vmbeep.ecoff
quiet_cmd_ecoff = ECOFF   $@
      cmd_ecoff = $(obj)/elf2ecoff $(VMBEEP) $@ $(e2eflag)
$(obj)/vmbeep.ecoff: $(obj)/elf2ecoff $(VMBEEP) FORCE
	$(call if_changed,ecoff)

targets += vmbeep.bin
quiet_cmd_bin = OBJCOPY $@
      cmd_bin = $(OBJCOPY) -O binary $(strip-flags) $(VMBEEP) $@
$(obj)/vmbeep.bin: $(VMBEEP) FORCE
	$(call if_changed,bin)

targets += vmbeep.srec
quiet_cmd_srec = OBJCOPY $@
      cmd_srec = $(OBJCOPY) -S -O srec $(strip-flags) $(VMBEEP) $@
$(obj)/vmbeep.srec: $(VMBEEP) FORCE
	$(call if_changed,srec)
