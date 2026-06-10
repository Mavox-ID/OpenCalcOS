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
#ifndef __ASM_SH_TRAPS_64_H
#define __ASM_SH_TRAPS_64_H

#include <cpu/registers.h>

extern void phys_stext(void);

#define lookup_exception_vector()		\
({						\
	unsigned long _vec;			\
						\
	__asm__ __volatile__ (			\
		"getcon " __EXPEVT ", %0\n\t"	\
		: "=r" (_vec)			\
	);					\
						\
	_vec;					\
})

static inline void trigger_address_error(void)
{
	phys_stext();
}

#define BUILD_TRAP_HANDLER(name)	\
asmlinkage void name##_trap_handler(unsigned int vec, struct pt_regs *regs)
#define TRAP_HANDLER_DECL

#endif /* __ASM_SH_TRAPS_64_H */
