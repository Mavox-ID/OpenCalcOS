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
#include <beep/types.h>
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/interrupt.h>
#include <beep/irq.h>
#include <beep/io.h>
#include <asm/coldfire.h>
#include <asm/mcfsim.h>

static void intc2_irq_gpio_mask(struct irq_data *d)
{
	u32 imr = readl(MCFSIM2_GPIOINTENABLE);
	u32 type = irqd_get_trigger_type(d);
	int irq = d->irq - MCF_IRQ_GPIO0;

	if (type & IRQ_TYPE_EDGE_RISING)
		imr &= ~(0x001 << irq);
	if (type & IRQ_TYPE_EDGE_FALLING)
		imr &= ~(0x100 << irq);
	writel(imr, MCFSIM2_GPIOINTENABLE);
}

static void intc2_irq_gpio_unmask(struct irq_data *d)
{
	u32 imr = readl(MCFSIM2_GPIOINTENABLE);
	u32 type = irqd_get_trigger_type(d);
	int irq = d->irq - MCF_IRQ_GPIO0;

	if (type & IRQ_TYPE_EDGE_RISING)
		imr |= (0x001 << irq);
	if (type & IRQ_TYPE_EDGE_FALLING)
		imr |= (0x100 << irq);
	writel(imr, MCFSIM2_GPIOINTENABLE);
}

static void intc2_irq_gpio_ack(struct irq_data *d)
{
	u32 imr = 0;
	u32 type = irqd_get_trigger_type(d);
	int irq = d->irq - MCF_IRQ_GPIO0;

	if (type & IRQ_TYPE_EDGE_RISING)
		imr |= (0x001 << irq);
	if (type & IRQ_TYPE_EDGE_FALLING)
		imr |= (0x100 << irq);
	writel(imr, MCFSIM2_GPIOINTCLEAR);
}

static int intc2_irq_gpio_set_type(struct irq_data *d, unsigned int f)
{
	if (f & ~IRQ_TYPE_EDGE_BOTH)
		return -EINVAL;
	return 0;
}

static struct irq_chip intc2_irq_gpio_chip = {
	.name		= "CF-INTC2",
	.irq_mask	= intc2_irq_gpio_mask,
	.irq_unmask	= intc2_irq_gpio_unmask,
	.irq_ack	= intc2_irq_gpio_ack,
	.irq_set_type	= intc2_irq_gpio_set_type,
};

static int __init mcf_intc2_init(void)
{
	int irq;

	/* set the interrupt base for the second interrupt controller */
	writel(MCFINTC2_VECBASE, MCFINTC2_INTBASE);

	/* GPIO interrupt sources */
	for (irq = MCF_IRQ_GPIO0; (irq <= MCF_IRQ_GPIO6); irq++) {
		irq_set_chip(irq, &intc2_irq_gpio_chip);
		irq_set_handler(irq, handle_edge_irq);
	}

	return 0;
}

arch_initcall(mcf_intc2_init);
