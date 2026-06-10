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
#include <beep/jump_label.h>
#include <beep/kernel.h>
#include <beep/memory.h>
#include <beep/mutex.h>
#include <beep/types.h>
#include <beep/cpu.h>

#include <asm/cacheflush.h>
#include <asm/inst.h>

#ifdef HAVE_JUMP_LABEL

#define J_RANGE_MASK ((1ul << 28) - 1)

void arch_jump_label_transform(struct jump_entry *e,
			       enum jump_label_type type)
{
	union mips_instruction insn;
	union mips_instruction *insn_p =
		(union mips_instruction *)(unsigned long)e->code;

	/* Jump only works within a 256MB aligned region. */
	BUG_ON((e->target & ~J_RANGE_MASK) != (e->code & ~J_RANGE_MASK));

	/* Target must have 4 byte alignment. */
	BUG_ON((e->target & 3) != 0);

	if (type == JUMP_LABEL_ENABLE) {
		insn.j_format.opcode = j_op;
		insn.j_format.target = (e->target & J_RANGE_MASK) >> 2;
	} else {
		insn.word = 0; /* nop */
	}

	get_online_cpus();
	mutex_lock(&text_mutex);
	*insn_p = insn;

	flush_icache_range((unsigned long)insn_p,
			   (unsigned long)insn_p + sizeof(*insn_p));

	mutex_unlock(&text_mutex);
	put_online_cpus();
}

#endif /* HAVE_JUMP_LABEL */
