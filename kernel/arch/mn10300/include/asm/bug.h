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
#ifndef _ASM_BUG_H
#define _ASM_BUG_H

#ifdef CONFIG_BUG

/*
 * Tell the user there is some problem.
 */
#define BUG()							\
do {								\
	asm volatile(						\
		"	syscall 15			\n"	\
		"0:					\n"	\
		"	.section __bug_table,\"a\"	\n"	\
		"	.long 0b,%0,%1			\n"	\
		"	.previous			\n"	\
		:						\
		: "i"(__FILE__), "i"(__LINE__)			\
		);						\
} while (1)

#define HAVE_ARCH_BUG
#endif /* CONFIG_BUG */

#include <asm-generic/bug.h>

#endif /* _ASM_BUG_H */
