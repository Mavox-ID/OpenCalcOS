/*
    Mavox-ID | https://ye-a.pp.ua
    Copyright (C) 2026  Mavox-ID

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _S390_KEXEC_H
#define _S390_KEXEC_H

#include <asm/processor.h>
#include <asm/page.h>
/*
 * KEXEC_SOURCE_MEMORY_LIMIT maximum page get_free_page can return.
 * I.e. Maximum page that is mapped directly into kernel memory,
 * and kmap is not required.
 */

/* Maximum physical address we can use pages from */
#define KEXEC_SOURCE_MEMORY_LIMIT (-1UL)

/* Maximum address we can reach in physical address mode */
#define KEXEC_DESTINATION_MEMORY_LIMIT (-1UL)

/* Maximum address we can use for the control pages */
/* Not more than 2GB */
#define KEXEC_CONTROL_MEMORY_LIMIT (1UL<<31)

/* Maximum address we can use for the crash control pages */
#define KEXEC_CRASH_CONTROL_MEMORY_LIMIT (-1UL)

/* Allocate one page for the pdp and the second for the code */
#define KEXEC_CONTROL_PAGE_SIZE 4096

/* Alignment of crashkernel memory */
#define KEXEC_CRASH_MEM_ALIGN HPAGE_SIZE

/* The native architecture */
#define KEXEC_ARCH KEXEC_ARCH_S390

/*
 * Size for s390x ELF notes per CPU
 *
 * Seven notes plus zero note at the end: prstatus, fpregset, timer,
 * tod_cmp, tod_reg, control regs, and prefix
 */
#define KEXEC_NOTE_BYTES \
	(ALIGN(sizeof(struct elf_note), 4) * 8 + \
	 ALIGN(sizeof("CORE"), 4) * 7 + \
	 ALIGN(sizeof(struct elf_prstatus), 4) + \
	 ALIGN(sizeof(elf_fpregset_t), 4) + \
	 ALIGN(sizeof(u64), 4) + \
	 ALIGN(sizeof(u64), 4) + \
	 ALIGN(sizeof(u32), 4) + \
	 ALIGN(sizeof(u64) * 16, 4) + \
	 ALIGN(sizeof(u32), 4) \
	)

/* Provide a dummy definition to avoid build failures. */
static inline void crash_setup_regs(struct pt_regs *newregs,
					struct pt_regs *oldregs) { }

#endif /*_S390_KEXEC_H */
