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
#include <beep/sched.h>
#include <beep/irq.h>

#include "proto.h"
#include "irq_impl.h"


/*
 * Is the palcode SMP safe? In other words: can we call cserve_ena/dis
 * at the same time in multiple CPUs? To be safe I added a spinlock
 * but it can be removed trivially if the palcode is robust against smp.
 */
DEFINE_SPINLOCK(srm_irq_lock);

static inline void
srm_enable_irq(struct irq_data *d)
{
	spin_lock(&srm_irq_lock);
	cserve_ena(d->irq - 16);
	spin_unlock(&srm_irq_lock);
}

static void
srm_disable_irq(struct irq_data *d)
{
	spin_lock(&srm_irq_lock);
	cserve_dis(d->irq - 16);
	spin_unlock(&srm_irq_lock);
}

/* Handle interrupts from the SRM, assuming no additional weirdness.  */
static struct irq_chip srm_irq_type = {
	.name		= "SRM",
	.irq_unmask	= srm_enable_irq,
	.irq_mask	= srm_disable_irq,
	.irq_mask_ack	= srm_disable_irq,
};

void __init
init_srm_irqs(long max, unsigned long ignore_mask)
{
	long i;

	if (NR_IRQS <= 16)
		return;
	for (i = 16; i < max; ++i) {
		if (i < 64 && ((ignore_mask >> i) & 1))
			continue;
		irq_set_chip_and_handler(i, &srm_irq_type, handle_level_irq);
		irq_set_status_flags(i, IRQ_LEVEL);
	}
}

void 
srm_device_interrupt(unsigned long vector)
{
	int irq = (vector - 0x800) >> 4;
	handle_irq(irq);
}
