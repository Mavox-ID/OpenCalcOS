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
#ifndef __ASM_ARM_MACH_IRQ_H
#define __ASM_ARM_MACH_IRQ_H

#include <beep/irq.h>

struct seq_file;

/*
 * This is internal.  Do not use it.
 */
extern void init_FIQ(int);
extern int show_fiq_list(struct seq_file *, int);

#ifdef CONFIG_MULTI_IRQ_HANDLER
extern void (*handle_arch_irq)(struct pt_regs *);
#endif

/*
 * This is for easy migration, but should be changed in the source
 */
#define do_bad_IRQ(irq,desc)				\
do {							\
	raw_spin_lock(&desc->lock);			\
	handle_bad_irq(irq, desc);			\
	raw_spin_unlock(&desc->lock);			\
} while(0)

#ifndef __ASSEMBLY__
/*
 * Entry/exit functions for chained handlers where the primary IRQ chip
 * may implement either fasteoi or level-trigger flow control.
 */
static inline void chained_irq_enter(struct irq_chip *chip,
				     struct irq_desc *desc)
{
	/* FastEOI controllers require no action on entry. */
	if (chip->irq_eoi)
		return;

	if (chip->irq_mask_ack) {
		chip->irq_mask_ack(&desc->irq_data);
	} else {
		chip->irq_mask(&desc->irq_data);
		if (chip->irq_ack)
			chip->irq_ack(&desc->irq_data);
	}
}

static inline void chained_irq_exit(struct irq_chip *chip,
				    struct irq_desc *desc)
{
	if (chip->irq_eoi)
		chip->irq_eoi(&desc->irq_data);
	else
		chip->irq_unmask(&desc->irq_data);
}
#endif

#endif
