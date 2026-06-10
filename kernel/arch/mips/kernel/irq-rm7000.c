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
#include <beep/irq.h>
#include <beep/kernel.h>

#include <asm/irq_cpu.h>
#include <asm/mipsregs.h>

static inline void unmask_rm7k_irq(struct irq_data *d)
{
	set_c0_intcontrol(0x100 << (d->irq - RM7K_CPU_IRQ_BASE));
}

static inline void mask_rm7k_irq(struct irq_data *d)
{
	clear_c0_intcontrol(0x100 << (d->irq - RM7K_CPU_IRQ_BASE));
}

static struct irq_chip rm7k_irq_controller = {
	.name = "RM7000",
	.irq_ack = mask_rm7k_irq,
	.irq_mask = mask_rm7k_irq,
	.irq_mask_ack = mask_rm7k_irq,
	.irq_unmask = unmask_rm7k_irq,
	.irq_eoi = unmask_rm7k_irq
};

void __init rm7k_cpu_irq_init(void)
{
	int base = RM7K_CPU_IRQ_BASE;
	int i;

	clear_c0_intcontrol(0x00000f00);		/* Mask all */

	for (i = base; i < base + 4; i++)
		irq_set_chip_and_handler(i, &rm7k_irq_controller,
					 handle_percpu_irq);
}
