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
#ifndef _BLACKFIN_BUG_H
#define _BLACKFIN_BUG_H

#ifdef CONFIG_BUG

/*
 * This can be any undefined 16-bit opcode, meaning
 * ((opcode & 0xc000) != 0xc000)
 * Anything from 0x0001 to 0x000A (inclusive) will work
 */
#define BFIN_BUG_OPCODE	0x0001

#ifdef CONFIG_DEBUG_BUGVERBOSE

#define _BUG_OR_WARN(flags)						\
	asm volatile(							\
		"1:	.hword	%0\n"					\
		"	.section __bug_table,\"a\",@progbits\n"		\
		"2:	.long	1b\n"					\
		"	.long	%1\n"					\
		"	.short	%2\n"					\
		"	.short	%3\n"					\
		"	.org	2b + %4\n"				\
		"	.previous"					\
		:							\
		: "i"(BFIN_BUG_OPCODE), "i"(__FILE__),			\
		  "i"(__LINE__), "i"(flags),				\
		  "i"(sizeof(struct bug_entry)))

#else

#define _BUG_OR_WARN(flags)						\
	asm volatile(							\
		"1:	.hword	%0\n"					\
		"	.section __bug_table,\"a\",@progbits\n"		\
		"2:	.long	1b\n"					\
		"	.short	%1\n"					\
		"	.org	2b + %2\n"				\
		"	.previous"					\
		:							\
		: "i"(BFIN_BUG_OPCODE), "i"(flags),			\
		  "i"(sizeof(struct bug_entry)))

#endif /* CONFIG_DEBUG_BUGVERBOSE */

#define BUG()								\
	do {								\
		_BUG_OR_WARN(0);					\
		unreachable();						\
	} while (0)

#define WARN_ON(condition)							\
	({								\
		int __ret_warn_on = !!(condition);			\
		if (unlikely(__ret_warn_on))				\
			_BUG_OR_WARN(BUGFLAG_WARNING);			\
		unlikely(__ret_warn_on);				\
	})

#define HAVE_ARCH_BUG
#define HAVE_ARCH_WARN_ON

#endif

#include <asm-generic/bug.h>

#endif
