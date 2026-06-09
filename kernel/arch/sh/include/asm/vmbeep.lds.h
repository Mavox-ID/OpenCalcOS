#ifndef __ASM_SH_VMBEEP_LDS_H
#define __ASM_SH_VMBEEP_LDS_H

#include <asm-generic/vmbeep.lds.h>

#ifdef CONFIG_DWARF_UNWINDER
#define DWARF_EH_FRAME							\
	.eh_frame : AT(ADDR(.eh_frame) - LOAD_OFFSET) {			\
		  VMBEEP_SYMBOL(__start_eh_frame) = .;			\
		  *(.eh_frame)						\
		  VMBEEP_SYMBOL(__stop_eh_frame) = .;			\
	}
#else
#define DWARF_EH_FRAME
#endif

#ifdef CONFIG_SUPERH64
#define EXTRA_TEXT		\
	*(.text64)		\
	*(.text..SHmedia32)
#else
#define EXTRA_TEXT
#endif

#endif /* __ASM_SH_VMBEEP_LDS_H */
