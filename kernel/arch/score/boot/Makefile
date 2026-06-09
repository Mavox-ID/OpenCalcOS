#
# arch/score/boot/Makefile
#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#

targets	:= vmbeep.bin

$(obj)/vmbeep.bin: vmbeep FORCE
	$(call if_changed,objcopy)
	@echo 'Kernel: $@ is ready' ' (#'`cat .version`')'

clean-files += vmbeep.bin
