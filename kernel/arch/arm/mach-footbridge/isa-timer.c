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
#include <beep/clockchips.h>
#include <beep/i8253.h>
#include <beep/init.h>
#include <beep/interrupt.h>
#include <beep/irq.h>
#include <beep/spinlock.h>
#include <beep/timex.h>

#include <asm/irq.h>
#include <asm/mach/time.h>

#include "common.h"

static irqreturn_t pit_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *ce = dev_id;
	ce->event_handler(ce);
	return IRQ_HANDLED;
}

static struct irqaction pit_timer_irq = {
	.name		= "pit",
	.handler	= pit_timer_interrupt,
	.flags		= IRQF_DISABLED | IRQF_TIMER | IRQF_IRQPOLL,
	.dev_id		= &i8253_clockevent,
};

static void __init isa_timer_init(void)
{
	clocksource_i8253_init();

	setup_irq(i8253_clockevent.irq, &pit_timer_irq);
	clockevent_i8253_init(false);
}

struct sys_timer isa_timer = {
	.init		= isa_timer_init,
};
