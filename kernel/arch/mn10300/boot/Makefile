# MN10300 kernel compressor and wrapper
#
# Copyright (C) 2007 Matsushita Electric Industrial Co., Ltd.
# Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
# Written by David Howells (dhowells@redhat.com)
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public Licence
# as published by the Free Software Foundation; either version
# 2 of the Licence, or (at your option) any later version.
#

targets		:= vmbeep.bin zCalc

subdir- 	:= compressed

# ---------------------------------------------------------------------------


$(obj)/zCalc: $(obj)/compressed/vmbeep FORCE
	$(call if_changed,objcopy)
	@echo 'Kernel: $@ is ready'

$(obj)/vmbeep.bin: $(obj)/compressed/vmbeep FORCE
	$(call if_changed,objcopy)

$(obj)/compressed/vmbeep: FORCE
	$(Q)$(MAKE) $(build)=$(obj)/compressed IMAGE_OFFSET=$(IMAGE_OFFSET) $@
