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
#include <beep/irq.h>
#include <beep/export.h>

#include "internals.h"

/*
 * What should we do if we get a hw irq event on an illegal vector?
 * Each architecture has to answer this themself.
 */
static void ack_bad(struct irq_data *data)
{
	struct irq_desc *desc = irq_data_to_desc(data);

	print_irq_desc(data->irq, desc);
	ack_bad_irq(data->irq);
}

/*
 * NOP functions
 */
static void noop(struct irq_data *data) { }

static unsigned int noop_ret(struct irq_data *data)
{
	return 0;
}

/*
 * Generic no controller implementation
 */
struct irq_chip no_irq_chip = {
	.name		= "none",
	.irq_startup	= noop_ret,
	.irq_shutdown	= noop,
	.irq_enable	= noop,
	.irq_disable	= noop,
	.irq_ack	= ack_bad,
};

/*
 * Generic dummy implementation which can be used for
 * real dumb interrupt sources
 */
struct irq_chip dummy_irq_chip = {
	.name		= "dummy",
	.irq_startup	= noop_ret,
	.irq_shutdown	= noop,
	.irq_enable	= noop,
	.irq_disable	= noop,
	.irq_ack	= noop,
	.irq_mask	= noop,
	.irq_unmask	= noop,
};
EXPORT_SYMBOL_GPL(dummy_irq_chip);
