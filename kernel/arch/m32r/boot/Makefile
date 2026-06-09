#
# arch/m32r/boot/Makefile
#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.

targets := zCalc
subdir- := compressed

obj-y	:= setup.o

$(obj)/zCalc: $(obj)/compressed/vmbeep FORCE
	$(call if_changed,objcopy)
	@echo 'Kernel: $@ is ready'

$(obj)/compressed/vmbeep: FORCE
	$(Q)$(MAKE) $(build)=$(obj)/compressed $@

