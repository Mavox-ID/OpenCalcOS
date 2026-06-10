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
#include <beep/kernel.h>
#include <beep/spinlock.h>
#include <beep/device.h>
#include <beep/types.h>
#include <beep/irq.h>
#include <beep/io.h>

#include <plat/wakeup-mask.h>
#include <plat/pm.h>

void samsung_sync_wakemask(void __iomem *reg,
			   struct samsung_wakeup_mask *mask, int nr_mask)
{
	struct irq_data *data;
	u32 val;

	val = __raw_readl(reg);

	for (; nr_mask > 0; nr_mask--, mask++) {
		if (mask->irq == NO_WAKEUP_IRQ) {
			val |= mask->bit;
			continue;
		}

		data = irq_get_irq_data(mask->irq);

		/* bit of a liberty to read this directly from irq_data. */
		if (irqd_is_wakeup_set(data))
			val &= ~mask->bit;
		else
			val |= mask->bit;
	}

	printk(KERN_INFO "wakemask %08x => %08x\n", __raw_readl(reg), val);
	__raw_writel(val, reg);
}
