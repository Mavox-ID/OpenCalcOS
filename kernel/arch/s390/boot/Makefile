#
# Makefile for the beep s390-specific parts of the memory manager.
#

COMPILE_VERSION := __beep_compile_version_id__`hostname |  \
			tr -c '[0-9A-Za-z]' '_'`__`date | \
			tr -c '[0-9A-Za-z]' '_'`_t

ccflags-y  := -DCOMPILE_VERSION=$(COMPILE_VERSION) -gstabs -I.

targets := image
targets += bzImage
subdir- := compressed

$(obj)/image: vmbeep FORCE
	$(call if_changed,objcopy)

$(obj)/bzImage: $(obj)/compressed/vmbeep FORCE
	$(call if_changed,objcopy)

$(obj)/compressed/vmbeep: FORCE
	$(Q)$(MAKE) $(build)=$(obj)/compressed $@

install: $(CONFIGURE) $(obj)/image
	sh -x  $(srctree)/$(obj)/install.sh $(KERNELRELEASE) $(obj)/image \
	      System.map "$(INSTALL_PATH)"
