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
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/irq.h>
#include <beep/interrupt.h>
#include <beep/pci.h>

#include <asm/i8259.h>
#include <asm/irq_cpu.h>
#include <asm/irq_gt641xx.h>
#include <asm/gt64120.h>

#include <irq.h>

asmlinkage void plat_irq_dispatch(void)
{
	unsigned pending = read_c0_status() & read_c0_cause() & ST0_IM;
	int irq;

	if (pending & CAUSEF_IP2)
		gt641xx_irq_dispatch();
	else if (pending & CAUSEF_IP6) {
		irq = i8259_irq();
		if (irq < 0)
			spurious_interrupt();
		else
			do_IRQ(irq);
	} else if (pending & CAUSEF_IP3)
		do_IRQ(MIPS_CPU_IRQ_BASE + 3);
	else if (pending & CAUSEF_IP4)
		do_IRQ(MIPS_CPU_IRQ_BASE + 4);
	else if (pending & CAUSEF_IP5)
		do_IRQ(MIPS_CPU_IRQ_BASE + 5);
	else if (pending & CAUSEF_IP7)
		do_IRQ(MIPS_CPU_IRQ_BASE + 7);
	else
		spurious_interrupt();
}

static struct irqaction cascade = {
	.handler	= no_action,
	.name		= "cascade",
	.flags		= IRQF_NO_THREAD,
};

void __init arch_init_irq(void)
{
	mips_cpu_irq_init();
	gt641xx_irq_init();
	init_i8259_irqs();

	setup_irq(GT641XX_CASCADE_IRQ, &cascade);
	setup_irq(I8259_CASCADE_IRQ, &cascade);
}
