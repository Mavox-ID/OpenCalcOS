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
#ifndef __ASM_AVR32_KPROBES_H
#define __ASM_AVR32_KPROBES_H

#include <beep/types.h>

typedef u16	kprobe_opcode_t;
#define BREAKPOINT_INSTRUCTION	0xd673	/* breakpoint */
#define MAX_INSN_SIZE		2

#define kretprobe_blacklist_size 0

#define arch_remove_kprobe(p)	do { } while (0)

/* Architecture specific copy of original instruction */
struct arch_specific_insn {
	kprobe_opcode_t	insn[MAX_INSN_SIZE];
};

extern int kprobe_fault_handler(struct pt_regs *regs, int trapnr);
extern int kprobe_exceptions_notify(struct notifier_block *self,
				    unsigned long val, void *data);

#define flush_insn_slot(p)	do { } while (0)

#endif /* __ASM_AVR32_KPROBES_H */
