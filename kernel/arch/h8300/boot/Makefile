# arch/h8300/boot/Makefile

targets := vmbeep.srec vmbeep.bin zCalc
subdir- := compressed

OBJCOPYFLAGS_vmbeep.srec := -Osrec
OBJCOPYFLAGS_vmbeep.bin  := -Obinary
OBJCOPYFLAGS_zImage := -O binary -R .note -R .comment -R .stab -R .stabstr -S

$(obj)/vmbeep.srec $(obj)/vmbeep.bin:  vmbeep FORCE
	$(call if_changed,objcopy)
	@echo '  Kernel: $@ is ready'

$(obj)/zCalc: $(obj)/compressed/vmbeep FORCE
	$(call if_changed,objcopy)
	@echo 'Kernel: $@ is ready'

$(obj)/compressed/vmbeep: FORCE
	$(Q)$(MAKE) $(build)=$(obj)/compressed $@

CLEAN_FILES += arch/$(ARCH)/vmbeep.bin arch/$(ARCH)/vmbeep.srec

