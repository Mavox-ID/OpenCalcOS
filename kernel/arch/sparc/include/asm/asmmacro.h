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
#ifndef _SPARC_ASMMACRO_H
#define _SPARC_ASMMACRO_H

/* All trap entry points _must_ begin with this macro or else you
 * lose.  It makes sure the kernel has a proper window so that
 * c-code can be called.
 */
#define SAVE_ALL_HEAD \
	sethi	%hi(trap_setup), %l4; \
	jmpl	%l4 + %lo(trap_setup), %l6;
#define SAVE_ALL \
	SAVE_ALL_HEAD \
	 nop;

/* All traps low-level code here must end with this macro. */
#define RESTORE_ALL b ret_trap_entry; clr %l6;

/* Support for run-time patching of single instructions.
 * This is used to handle the differences in the ASI for
 * MMUREGS for LEON and SUN.
 *
 * Sample:
 * LEON_PI(lda [%g0] ASI_LEON_MMUREGS, %o0
 * SUN_PI_(lda [%g0] ASI_M_MMUREGS, %o0
 * PI == Patch Instruction
 *
 * For LEON we will use the first variant,
 * and for all other we will use the SUN variant.
 * The order is important.
 */
#define LEON_PI(...)				\
662:	__VA_ARGS__

#define SUN_PI_(...)				\
	.section .leon_1insn_patch, "ax";	\
	.word 662b;				\
	__VA_ARGS__;				\
	.previous

#endif /* !(_SPARC_ASMMACRO_H) */
