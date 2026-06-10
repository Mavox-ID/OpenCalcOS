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
#include <beep/kernel.h>
#include <beep/delay.h>
#include <beep/device.h>
#include <beep/smp.h>
#include <beep/jiffies.h>
#include <beep/percpu.h>
#include <beep/clockchips.h>
#include <beep/hardirq.h>
#include <beep/irq.h>

static DEFINE_PER_CPU(struct clock_event_device, local_clockevent);

/*
 * Used on SMP for either the local timer or SMP_MSG_TIMER
 */
void local_timer_interrupt(void)
{
	struct clock_event_device *clk = &__get_cpu_var(local_clockevent);

	irq_enter();
	clk->event_handler(clk);
	irq_exit();
}

static void dummy_timer_set_mode(enum clock_event_mode mode,
				 struct clock_event_device *clk)
{
}

void local_timer_setup(unsigned int cpu)
{
	struct clock_event_device *clk = &per_cpu(local_clockevent, cpu);

	clk->name		= "dummy_timer";
	clk->features		= CLOCK_EVT_FEAT_ONESHOT |
				  CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_DUMMY;
	clk->rating		= 400;
	clk->mult		= 1;
	clk->set_mode		= dummy_timer_set_mode;
	clk->broadcast		= smp_timer_broadcast;
	clk->cpumask		= cpumask_of(cpu);

	clockevents_register_device(clk);
}

void local_timer_stop(unsigned int cpu)
{
}
