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
#ifndef _ASM_MIPS_JUMP_LABEL_H
#define _ASM_MIPS_JUMP_LABEL_H

#include <beep/types.h>

#ifdef __KERNEL__

#define JUMP_LABEL_NOP_SIZE 4

#ifdef CONFIG_64BIT
#define WORD_INSN ".dword"
#else
#define WORD_INSN ".word"
#endif

static __always_inline bool arch_static_branch(struct static_key *key)
{
	asm goto("1:\tnop\n\t"
		"nop\n\t"
		".pushsection __jump_table,  \"aw\"\n\t"
		WORD_INSN " 1b, %l[l_yes], %0\n\t"
		".popsection\n\t"
		: :  "i" (key) : : l_yes);
	return false;
l_yes:
	return true;
}

#endif /* __KERNEL__ */

#ifdef CONFIG_64BIT
typedef u64 jump_label_t;
#else
typedef u32 jump_label_t;
#endif

struct jump_entry {
	jump_label_t code;
	jump_label_t target;
	jump_label_t key;
};

#endif /* _ASM_MIPS_JUMP_LABEL_H */
