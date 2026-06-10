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
#include <beep/interrupt.h>
#include <beep/list.h>
#include <asm/mach/irq.h>
#include <asm/irq.h>
#include <mach/hardware.h>
#include <asm/mach-types.h>

static u32 iop33x_mask0;
static u32 iop33x_mask1;

static void intctl0_write(u32 val)
{
	asm volatile("mcr p6, 0, %0, c0, c0, 0" : : "r" (val));
}

static void intctl1_write(u32 val)
{
	asm volatile("mcr p6, 0, %0, c1, c0, 0" : : "r" (val));
}

static void intstr0_write(u32 val)
{
	asm volatile("mcr p6, 0, %0, c2, c0, 0" : : "r" (val));
}

static void intstr1_write(u32 val)
{
	asm volatile("mcr p6, 0, %0, c3, c0, 0" : : "r" (val));
}

static void intbase_write(u32 val)
{
	asm volatile("mcr p6, 0, %0, c12, c0, 0" : : "r" (val));
}

static void intsize_write(u32 val)
{
	asm volatile("mcr p6, 0, %0, c13, c0, 0" : : "r" (val));
}

static void
iop33x_irq_mask1 (struct irq_data *d)
{
	iop33x_mask0 &= ~(1 << d->irq);
	intctl0_write(iop33x_mask0);
}

static void
iop33x_irq_mask2 (struct irq_data *d)
{
	iop33x_mask1 &= ~(1 << (d->irq - 32));
	intctl1_write(iop33x_mask1);
}

static void
iop33x_irq_unmask1(struct irq_data *d)
{
	iop33x_mask0 |= 1 << d->irq;
	intctl0_write(iop33x_mask0);
}

static void
iop33x_irq_unmask2(struct irq_data *d)
{
	iop33x_mask1 |= (1 << (d->irq - 32));
	intctl1_write(iop33x_mask1);
}

struct irq_chip iop33x_irqchip1 = {
	.name		= "IOP33x-1",
	.irq_ack	= iop33x_irq_mask1,
	.irq_mask	= iop33x_irq_mask1,
	.irq_unmask	= iop33x_irq_unmask1,
};

struct irq_chip iop33x_irqchip2 = {
	.name		= "IOP33x-2",
	.irq_ack	= iop33x_irq_mask2,
	.irq_mask	= iop33x_irq_mask2,
	.irq_unmask	= iop33x_irq_unmask2,
};

void __init iop33x_init_irq(void)
{
	int i;

	iop_init_cp6_handler();

	intctl0_write(0);
	intctl1_write(0);
	intstr0_write(0);
	intstr1_write(0);
	intbase_write(0);
	intsize_write(1);
	if (machine_is_iq80331())
		*IOP3XX_PCIIRSR = 0x0f;

	for (i = 0; i < NR_IRQS; i++) {
		irq_set_chip_and_handler(i,
					 (i < 32) ? &iop33x_irqchip1 : &iop33x_irqchip2,
					 handle_level_irq);
		set_irq_flags(i, IRQF_VALID | IRQF_PROBE);
	}
}
