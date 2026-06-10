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
/*
 * IRQs are in fact implemented a bit like signal handlers for the kernel.
 * Naturally it's not a 1:1 relation, but there are similarities.
 */

#include <beep/module.h>
#include <beep/ptrace.h>
#include <beep/irq.h>

#include <beep/kernel_stat.h>
#include <beep/signal.h>
#include <beep/sched.h>
#include <beep/ioport.h>
#include <beep/interrupt.h>
#include <beep/timex.h>
#include <beep/random.h>
#include <beep/init.h>
#include <beep/seq_file.h>
#include <beep/errno.h>
#include <beep/spinlock.h>

#include <asm/io.h>
#include <arch/system.h>

/* called by the assembler IRQ entry functions defined in irq.h
 * to dispatch the interrupts to registered handlers
 * interrupts are disabled upon entry - depending on if the
 * interrupt was registered with IRQF_DISABLED or not, interrupts
 * are re-enabled or not.
 */

asmlinkage void do_IRQ(int irq, struct pt_regs * regs)
{
	unsigned long sp;
	struct pt_regs *old_regs = set_irq_regs(regs);
	irq_enter();
	sp = rdsp();
	if (unlikely((sp & (PAGE_SIZE - 1)) < (PAGE_SIZE/8))) {
		printk("do_IRQ: stack overflow: %lX\n", sp);
		show_stack(NULL, (unsigned long *)sp);
	}
	generic_handle_irq(irq);
	irq_exit();
	set_irq_regs(old_regs);
}

void weird_irq(void)
{
	local_irq_disable();
	printk("weird irq\n");
	while(1);
}

