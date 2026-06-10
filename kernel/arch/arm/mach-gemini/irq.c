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
#include <beep/init.h>
#include <beep/io.h>
#include <beep/ioport.h>
#include <beep/stddef.h>
#include <beep/list.h>
#include <beep/sched.h>
#include <asm/irq.h>
#include <asm/mach/irq.h>
#include <asm/system_misc.h>
#include <mach/hardware.h>

#define IRQ_SOURCE(base_addr)	(base_addr + 0x00)
#define IRQ_MASK(base_addr)	(base_addr + 0x04)
#define IRQ_CLEAR(base_addr)	(base_addr + 0x08)
#define IRQ_TMODE(base_addr)	(base_addr + 0x0C)
#define IRQ_TLEVEL(base_addr)	(base_addr + 0x10)
#define IRQ_STATUS(base_addr)	(base_addr + 0x14)
#define FIQ_SOURCE(base_addr)	(base_addr + 0x20)
#define FIQ_MASK(base_addr)	(base_addr + 0x24)
#define FIQ_CLEAR(base_addr)	(base_addr + 0x28)
#define FIQ_TMODE(base_addr)	(base_addr + 0x2C)
#define FIQ_LEVEL(base_addr)	(base_addr + 0x30)
#define FIQ_STATUS(base_addr)	(base_addr + 0x34)

static void gemini_ack_irq(struct irq_data *d)
{
	__raw_writel(1 << d->irq, IRQ_CLEAR(IO_ADDRESS(GEMINI_INTERRUPT_BASE)));
}

static void gemini_mask_irq(struct irq_data *d)
{
	unsigned int mask;

	mask = __raw_readl(IRQ_MASK(IO_ADDRESS(GEMINI_INTERRUPT_BASE)));
	mask &= ~(1 << d->irq);
	__raw_writel(mask, IRQ_MASK(IO_ADDRESS(GEMINI_INTERRUPT_BASE)));
}

static void gemini_unmask_irq(struct irq_data *d)
{
	unsigned int mask;

	mask = __raw_readl(IRQ_MASK(IO_ADDRESS(GEMINI_INTERRUPT_BASE)));
	mask |= (1 << d->irq);
	__raw_writel(mask, IRQ_MASK(IO_ADDRESS(GEMINI_INTERRUPT_BASE)));
}

static struct irq_chip gemini_irq_chip = {
	.name		= "INTC",
	.irq_ack	= gemini_ack_irq,
	.irq_mask	= gemini_mask_irq,
	.irq_unmask	= gemini_unmask_irq,
};

static struct resource irq_resource = {
	.name	= "irq_handler",
	.start	= IO_ADDRESS(GEMINI_INTERRUPT_BASE),
	.end	= IO_ADDRESS(FIQ_STATUS(GEMINI_INTERRUPT_BASE)) + 4,
};

void __init gemini_init_irq(void)
{
	unsigned int i, mode = 0, level = 0;

	/*
	 * Disable the idle handler by default since it is buggy
	 * For more info see arch/arm/mach-gemini/idle.c
	 */
	disable_hlt();

	request_resource(&iomem_resource, &irq_resource);

	for (i = 0; i < NR_IRQS; i++) {
		irq_set_chip(i, &gemini_irq_chip);
		if((i >= IRQ_TIMER1 && i <= IRQ_TIMER3) || (i >= IRQ_SERIRQ0 && i <= IRQ_SERIRQ1)) {
			irq_set_handler(i, handle_edge_irq);
			mode |= 1 << i;
			level |= 1 << i;
		} else {			
			irq_set_handler(i, handle_level_irq);
		}
		set_irq_flags(i, IRQF_VALID | IRQF_PROBE);
	}

	/* Disable all interrupts */
	__raw_writel(0, IRQ_MASK(IO_ADDRESS(GEMINI_INTERRUPT_BASE)));
	__raw_writel(0, FIQ_MASK(IO_ADDRESS(GEMINI_INTERRUPT_BASE)));

	/* Set interrupt mode */
	__raw_writel(mode, IRQ_TMODE(IO_ADDRESS(GEMINI_INTERRUPT_BASE)));
	__raw_writel(level, IRQ_TLEVEL(IO_ADDRESS(GEMINI_INTERRUPT_BASE)));
}
