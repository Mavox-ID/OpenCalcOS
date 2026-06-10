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
#include <beep/irq.h>
#include <beep/types.h>

#include <asm/dec/ioasic.h>
#include <asm/dec/ioasic_addrs.h>
#include <asm/dec/ioasic_ints.h>

static int ioasic_irq_base;

static void unmask_ioasic_irq(struct irq_data *d)
{
	u32 simr;

	simr = ioasic_read(IO_REG_SIMR);
	simr |= (1 << (d->irq - ioasic_irq_base));
	ioasic_write(IO_REG_SIMR, simr);
}

static void mask_ioasic_irq(struct irq_data *d)
{
	u32 simr;

	simr = ioasic_read(IO_REG_SIMR);
	simr &= ~(1 << (d->irq - ioasic_irq_base));
	ioasic_write(IO_REG_SIMR, simr);
}

static void ack_ioasic_irq(struct irq_data *d)
{
	mask_ioasic_irq(d);
	fast_iob();
}

static struct irq_chip ioasic_irq_type = {
	.name = "IO-ASIC",
	.irq_ack = ack_ioasic_irq,
	.irq_mask = mask_ioasic_irq,
	.irq_mask_ack = ack_ioasic_irq,
	.irq_unmask = unmask_ioasic_irq,
};

static struct irq_chip ioasic_dma_irq_type = {
	.name = "IO-ASIC-DMA",
	.irq_ack = ack_ioasic_irq,
	.irq_mask = mask_ioasic_irq,
	.irq_mask_ack = ack_ioasic_irq,
	.irq_unmask = unmask_ioasic_irq,
};

void __init init_ioasic_irqs(int base)
{
	int i;

	/* Mask interrupts. */
	ioasic_write(IO_REG_SIMR, 0);
	fast_iob();

	for (i = base; i < base + IO_INR_DMA; i++)
		irq_set_chip_and_handler(i, &ioasic_irq_type,
					 handle_level_irq);
	for (; i < base + IO_IRQ_LINES; i++)
		irq_set_chip(i, &ioasic_dma_irq_type);

	ioasic_irq_base = base;
}
