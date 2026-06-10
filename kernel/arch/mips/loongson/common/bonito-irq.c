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
#include <beep/interrupt.h>
#include <beep/compiler.h>

#include <loongson.h>

static inline void bonito_irq_enable(struct irq_data *d)
{
	LOONGSON_INTENSET = (1 << (d->irq - LOONGSON_IRQ_BASE));
	mmiowb();
}

static inline void bonito_irq_disable(struct irq_data *d)
{
	LOONGSON_INTENCLR = (1 << (d->irq - LOONGSON_IRQ_BASE));
	mmiowb();
}

static struct irq_chip bonito_irq_type = {
	.name		= "bonito_irq",
	.irq_mask	= bonito_irq_disable,
	.irq_unmask	= bonito_irq_enable,
};

static struct irqaction __maybe_unused dma_timeout_irqaction = {
	.handler	= no_action,
	.name		= "dma_timeout",
};

void bonito_irq_init(void)
{
	u32 i;

	for (i = LOONGSON_IRQ_BASE; i < LOONGSON_IRQ_BASE + 32; i++)
		irq_set_chip_and_handler(i, &bonito_irq_type,
					 handle_level_irq);

#ifdef CONFIG_CPU_LOONGSON2E
	setup_irq(LOONGSON_IRQ_BASE + 10, &dma_timeout_irqaction);
#endif
}
