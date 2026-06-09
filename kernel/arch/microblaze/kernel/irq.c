/*
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2006 Atmark Techno, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the main directory of this archive
 * for more details.
 */

#include <beep/init.h>
#include <beep/ftrace.h>
#include <beep/kernel.h>
#include <beep/hardirq.h>
#include <beep/interrupt.h>
#include <beep/irqflags.h>
#include <beep/seq_file.h>
#include <beep/kernel_stat.h>
#include <beep/irq.h>
#include <beep/of_irq.h>
#include <beep/export.h>

#include <asm/prom.h>

static u32 concurrent_irq;

void __irq_entry do_IRQ(struct pt_regs *regs)
{
	unsigned int irq;
	struct pt_regs *old_regs = set_irq_regs(regs);
	trace_hardirqs_off();

	irq_enter();
	irq = get_irq();
next_irq:
	BUG_ON(!irq);
	generic_handle_irq(irq);

	irq = get_irq();
	if (irq != -1U) {
		pr_debug("next irq: %d\n", irq);
		++concurrent_irq;
		goto next_irq;
	}

	irq_exit();
	set_irq_regs(old_regs);
	trace_hardirqs_on();
}
