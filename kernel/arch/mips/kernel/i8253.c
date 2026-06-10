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
#include <beep/export.h>
#include <beep/smp.h>
#include <beep/irq.h>

#include <asm/time.h>

static irqreturn_t timer_interrupt(int irq, void *dev_id)
{
	i8253_clockevent.event_handler(&i8253_clockevent);

	return IRQ_HANDLED;
}

static struct irqaction irq0  = {
	.handler = timer_interrupt,
	.flags = IRQF_NOBALANCING | IRQF_TIMER,
	.name = "timer"
};

void __init setup_pit_timer(void)
{
	clockevent_i8253_init(true);
	setup_irq(0, &irq0);
}

static int __init init_pit_clocksource(void)
{
	if (num_possible_cpus() > 1) /* PIT does not scale! */
		return 0;

	return clocksource_i8253_init();
}
arch_initcall(init_pit_clocksource);
