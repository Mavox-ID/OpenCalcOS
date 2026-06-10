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
#include <beep/init.h>
#include <beep/interrupt.h>
#include <beep/jiffies.h>
#include <beep/threads.h>
#include <asm/irq.h>
#include <asm/param.h>
#include <kern_util.h>
#include <os.h>

void timer_handler(int sig, struct siginfo *unused_si, struct uml_pt_regs *regs)
{
	unsigned long flags;

	local_irq_save(flags);
	do_IRQ(TIMER_IRQ, regs);
	local_irq_restore(flags);
}

static void itimer_set_mode(enum clock_event_mode mode,
			    struct clock_event_device *evt)
{
	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		set_interval();
		break;

	case CLOCK_EVT_MODE_SHUTDOWN:
	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_ONESHOT:
		disable_timer();
		break;

	case CLOCK_EVT_MODE_RESUME:
		break;
	}
}

static int itimer_next_event(unsigned long delta,
			     struct clock_event_device *evt)
{
	return timer_one_shot(delta + 1);
}

static struct clock_event_device itimer_clockevent = {
	.name		= "itimer",
	.rating		= 250,
	.cpumask	= cpu_all_mask,
	.features	= CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT,
	.set_mode	= itimer_set_mode,
	.set_next_event = itimer_next_event,
	.shift		= 32,
	.irq		= 0,
};

static irqreturn_t um_timer(int irq, void *dev)
{
	(*itimer_clockevent.event_handler)(&itimer_clockevent);

	return IRQ_HANDLED;
}

static cycle_t itimer_read(struct clocksource *cs)
{
	return os_nsecs() / 1000;
}

static struct clocksource itimer_clocksource = {
	.name		= "itimer",
	.rating		= 300,
	.read		= itimer_read,
	.mask		= CLOCKSOURCE_MASK(64),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
};

static void __init setup_itimer(void)
{
	int err;

	err = request_irq(TIMER_IRQ, um_timer, 0, "timer", NULL);
	if (err != 0)
		printk(KERN_ERR "register_timer : request_irq failed - "
		       "errno = %d\n", -err);

	itimer_clockevent.mult = div_sc(HZ, NSEC_PER_SEC, 32);
	itimer_clockevent.max_delta_ns =
		clockevent_delta2ns(60 * HZ, &itimer_clockevent);
	itimer_clockevent.min_delta_ns =
		clockevent_delta2ns(1, &itimer_clockevent);
	err = clocksource_register_hz(&itimer_clocksource, USEC_PER_SEC);
	if (err) {
		printk(KERN_ERR "clocksource_register_hz returned %d\n", err);
		return;
	}
	clockevents_register_device(&itimer_clockevent);
}

void read_persistent_clock(struct timespec *ts)
{
	long long nsecs = os_nsecs();

	set_normalized_timespec(ts, nsecs / NSEC_PER_SEC,
				nsecs % NSEC_PER_SEC);
}

void __init time_init(void)
{
	timer_init();
	late_time_init = setup_itimer;
}
