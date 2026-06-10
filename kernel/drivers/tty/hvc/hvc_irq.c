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

#include "hvc_console.h"

static irqreturn_t hvc_handle_interrupt(int irq, void *dev_instance)
{
	/* if hvc_poll request a repoll, then kick the hvcd thread */
	if (hvc_poll(dev_instance))
		hvc_kick();
	return IRQ_HANDLED;
}

/*
 * For IRQ based systems these callbacks can be used
 */
int notifier_add_irq(struct hvc_struct *hp, int irq)
{
	int rc;

	if (!irq) {
		hp->irq_requested = 0;
		return 0;
	}
	rc = request_irq(irq, hvc_handle_interrupt, 0,
			   "hvc_console", hp);
	if (!rc)
		hp->irq_requested = 1;
	return rc;
}

void notifier_del_irq(struct hvc_struct *hp, int irq)
{
	if (!hp->irq_requested)
		return;
	free_irq(irq, hp);
	hp->irq_requested = 0;
}

void notifier_hangup_irq(struct hvc_struct *hp, int irq)
{
	notifier_del_irq(hp, irq);
}
