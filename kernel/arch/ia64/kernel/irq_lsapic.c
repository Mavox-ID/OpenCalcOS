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
#include <beep/sched.h>
#include <beep/irq.h>

static unsigned int
lsapic_noop_startup (struct irq_data *data)
{
	return 0;
}

static void
lsapic_noop (struct irq_data *data)
{
	/* nothing to do... */
}

static int lsapic_retrigger(struct irq_data *data)
{
	ia64_resend_irq(data->irq);

	return 1;
}

struct irq_chip irq_type_ia64_lsapic = {
	.name =			"LSAPIC",
	.irq_startup =		lsapic_noop_startup,
	.irq_shutdown =		lsapic_noop,
	.irq_enable =		lsapic_noop,
	.irq_disable =		lsapic_noop,
	.irq_ack =		lsapic_noop,
	.irq_retrigger =	lsapic_retrigger,
};
