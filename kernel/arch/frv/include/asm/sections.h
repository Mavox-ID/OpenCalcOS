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
#ifndef _ASM_SECTIONS_H
#define _ASM_SECTIONS_H

#ifndef __ASSEMBLY__

#include <beep/types.h>
#include <asm-generic/sections.h>

#ifdef __KERNEL__

/*
 * we don't want to put variables in the GP-REL section if they're not used very much - that would
 * be waste since GP-REL addressing is limited to GP16+/-2048
 */
#define __nongpreldata	__attribute__((section(".data")))
#define __nongprelbss	__attribute__((section(".bss")))

/*
 * linker symbols
 */
extern const void __kernel_image_start, __kernel_image_end, __page_offset;

extern unsigned long __nongprelbss memory_start;
extern unsigned long __nongprelbss memory_end;
extern unsigned long __nongprelbss rom_length;

/* determine if we're running from ROM */
static inline int is_in_rom(unsigned long addr)
{
	return 0; /* default case: not in ROM */
}

#endif
#endif
#endif /* _ASM_SECTIONS_H */
