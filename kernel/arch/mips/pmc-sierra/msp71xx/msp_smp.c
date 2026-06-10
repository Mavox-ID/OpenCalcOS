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
#include <beep/smp.h>
#include <beep/interrupt.h>

#ifdef CONFIG_MIPS_MT_SMP
#define MIPS_CPU_IPI_RESCHED_IRQ 0	/* SW int 0 for resched */
#define MIPS_CPU_IPI_CALL_IRQ 1		/* SW int 1 for call */


static void ipi_resched_dispatch(void)
{
	do_IRQ(MIPS_CPU_IPI_RESCHED_IRQ);
}

static void ipi_call_dispatch(void)
{
	do_IRQ(MIPS_CPU_IPI_CALL_IRQ);
}

static irqreturn_t ipi_resched_interrupt(int irq, void *dev_id)
{
	return IRQ_HANDLED;
}

static irqreturn_t ipi_call_interrupt(int irq, void *dev_id)
{
	smp_call_function_interrupt();

	return IRQ_HANDLED;
}

static struct irqaction irq_resched = {
	.handler	= ipi_resched_interrupt,
	.flags		= IRQF_PERCPU,
	.name		= "IPI_resched"
};

static struct irqaction irq_call = {
	.handler	= ipi_call_interrupt,
	.flags		= IRQF_PERCPU,
	.name		= "IPI_call"
};

void __init arch_init_ipiirq(int irq, struct irqaction *action)
{
	setup_irq(irq, action);
	irq_set_handler(irq, handle_percpu_irq);
}

void __init msp_vsmp_int_init(void)
{
	set_vi_handler(MIPS_CPU_IPI_RESCHED_IRQ, ipi_resched_dispatch);
	set_vi_handler(MIPS_CPU_IPI_CALL_IRQ, ipi_call_dispatch);
	arch_init_ipiirq(MIPS_CPU_IPI_RESCHED_IRQ, &irq_resched);
	arch_init_ipiirq(MIPS_CPU_IPI_CALL_IRQ, &irq_call);
}
#endif /* CONFIG_MIPS_MT_SMP */
