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
#ifndef _ASM_KPROBES_H
#define _ASM_KPROBES_H

#include <beep/types.h>
#include <beep/ptrace.h>

struct kprobe;

typedef unsigned char kprobe_opcode_t;
#define BREAKPOINT_INSTRUCTION	0xff
#define MAX_INSN_SIZE 8
#define MAX_STACK_SIZE 128

/* Architecture specific copy of original instruction */
struct arch_specific_insn {
	/*  copy of original instruction
	 */
	kprobe_opcode_t insn[MAX_INSN_SIZE];
};

extern const int kretprobe_blacklist_size;

extern int kprobe_exceptions_notify(struct notifier_block *self,
				    unsigned long val, void *data);

#define flush_insn_slot(p)  do {} while (0)

extern void arch_remove_kprobe(struct kprobe *p);

#endif /* _ASM_KPROBES_H */
