#
# arch/cris/boot/Makefile
#

objcopyflags-$(CONFIG_ETRAX_ARCH_V10) += -R .note -R .comment
objcopyflags-$(CONFIG_ETRAX_ARCH_V32) += --remove-section=.bss --remove-section=.note.gnu.build-id

OBJCOPYFLAGS = -O binary $(objcopyflags-y)


subdir- := compressed rescue
targets := Image

$(obj)/Image: vmbeep FORCE
	$(call if_changed,objcopy)
	@echo '  Kernel: $@ is ready'

$(obj)/compressed/vmbeep: $(obj)/Image FORCE
	$(Q)$(MAKE) $(build)=$(obj)/compressed $@
	$(Q)$(MAKE) $(build)=$(obj)/rescue $(obj)/rescue/rescue.bin

$(obj)/zCalc:  $(obj)/compressed/vmbeep
	@cp $< $@
	@echo '  Kernel: $@ is ready'
