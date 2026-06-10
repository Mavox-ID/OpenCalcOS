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
#include <beep/module.h>
#include <beep/irq.h>

#include "irq-common.h"

int imx_irq_set_priority(unsigned char irq, unsigned char prio)
{
	struct irq_chip_generic *gc;
	struct mxc_extra_irq *exirq;
	int ret;

	ret = -ENOSYS;

	gc = irq_get_chip_data(irq);
	if (gc && gc->private) {
		exirq = gc->private;
		if (exirq->set_priority)
			ret = exirq->set_priority(irq, prio);
	}

	return ret;
}
EXPORT_SYMBOL(imx_irq_set_priority);

int mxc_set_irq_fiq(unsigned int irq, unsigned int type)
{
	struct irq_chip_generic *gc;
	struct mxc_extra_irq *exirq;
	int ret;

	ret = -ENOSYS;

	gc = irq_get_chip_data(irq);
	if (gc && gc->private) {
		exirq = gc->private;
		if (exirq->set_irq_fiq)
			ret = exirq->set_irq_fiq(irq, type);
	}

	return ret;
}
EXPORT_SYMBOL(mxc_set_irq_fiq);
