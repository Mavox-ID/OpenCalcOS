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
#include <beep/kallsyms.h>
#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/sched.h>
#include <asm/sysrq.h>

/* Catch non-i386 SUBARCH's. */
#if !defined(CONFIG_UML_X86) || defined(CONFIG_64BIT)
void show_trace(struct task_struct *task, unsigned long * stack)
{
	unsigned long addr;

	if (!stack) {
		stack = (unsigned long*) &stack;
		WARN_ON(1);
	}

	printk(KERN_INFO "Call Trace: \n");
	while (((long) stack & (THREAD_SIZE-1)) != 0) {
		addr = *stack;
		if (__kernel_text_address(addr)) {
			printk(KERN_INFO "%08lx:  [<%08lx>]",
			       (unsigned long) stack, addr);
			print_symbol(KERN_CONT " %s", addr);
			printk(KERN_CONT "\n");
		}
		stack++;
	}
	printk(KERN_INFO "\n");
}
#endif

/*
 * stack dumps generator - this is used by arch-independent code.
 * And this is identical to i386 currently.
 */
void dump_stack(void)
{
	unsigned long stack;

	show_trace(current, &stack);
}
EXPORT_SYMBOL(dump_stack);

/*Stolen from arch/i386/kernel/traps.c */
static const int kstack_depth_to_print = 24;

/* This recently started being used in arch-independent code too, as in
 * kernel/sched.c.*/
void show_stack(struct task_struct *task, unsigned long *esp)
{
	unsigned long *stack;
	int i;

	if (esp == NULL) {
		if (task != current && task != NULL) {
			esp = (unsigned long *) KSTK_ESP(task);
		} else {
			esp = (unsigned long *) &esp;
		}
	}

	stack = esp;
	for (i = 0; i < kstack_depth_to_print; i++) {
		if (kstack_end(stack))
			break;
		if (i && ((i % 8) == 0))
			printk(KERN_INFO "       ");
		printk(KERN_CONT "%08lx ", *stack++);
	}

	show_trace(task, esp);
}
