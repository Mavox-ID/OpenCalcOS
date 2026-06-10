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
#include <beep/io.h>
#include <beep/irq.h>
#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/topology.h>

static inline struct ipr_desc *get_ipr_desc(struct irq_data *data)
{
	struct irq_chip *chip = irq_data_get_irq_chip(data);
	return container_of(chip, struct ipr_desc, chip);
}

static void disable_ipr_irq(struct irq_data *data)
{
	struct ipr_data *p = irq_data_get_irq_chip_data(data);
	unsigned long addr = get_ipr_desc(data)->ipr_offsets[p->ipr_idx];
	/* Set the priority in IPR to 0 */
	__raw_writew(__raw_readw(addr) & (0xffff ^ (0xf << p->shift)), addr);
	(void)__raw_readw(addr);	/* Read back to flush write posting */
}

static void enable_ipr_irq(struct irq_data *data)
{
	struct ipr_data *p = irq_data_get_irq_chip_data(data);
	unsigned long addr = get_ipr_desc(data)->ipr_offsets[p->ipr_idx];
	/* Set priority in IPR back to original value */
	__raw_writew(__raw_readw(addr) | (p->priority << p->shift), addr);
}

/*
 * The shift value is now the number of bits to shift, not the number of
 * bits/4. This is to make it easier to read the value directly from the
 * datasheets. The IPR address is calculated using the ipr_offset table.
 */
void register_ipr_controller(struct ipr_desc *desc)
{
	int i;

	desc->chip.irq_mask = disable_ipr_irq;
	desc->chip.irq_unmask = enable_ipr_irq;

	for (i = 0; i < desc->nr_irqs; i++) {
		struct ipr_data *p = desc->ipr_data + i;
		int res;

		BUG_ON(p->ipr_idx >= desc->nr_offsets);
		BUG_ON(!desc->ipr_offsets[p->ipr_idx]);

		res = irq_alloc_desc_at(p->irq, numa_node_id());
		if (unlikely(res != p->irq && res != -EEXIST)) {
			printk(KERN_INFO "can not get irq_desc for %d\n",
			       p->irq);
			continue;
		}

		disable_irq_nosync(p->irq);
		irq_set_chip_and_handler_name(p->irq, &desc->chip,
					      handle_level_irq, "level");
		irq_set_chip_data(p->irq, p);
		disable_ipr_irq(irq_get_irq_data(p->irq));
	}
}
EXPORT_SYMBOL(register_ipr_controller);
