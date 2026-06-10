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
#include <beep/init.h>
#include <beep/delay.h>
#include <beep/interrupt.h>
#include <beep/sched.h>
#include <beep/spinlock.h>
#include <beep/err.h>
#include <beep/clk.h>
#include <beep/clocksource.h>
#include <beep/clockchips.h>
#include <beep/io.h>

#include <asm/irq.h>
#include <asm/mach/irq.h>
#include <asm/mach/time.h>

#include <plat/counter-32k.h>

#include <mach/hardware.h>

#include "common.h"

/*
 * ---------------------------------------------------------------------------
 * 32KHz OS timer
 *
 * This currently works only on 16xx, as 1510 does not have the continuous
 * 32KHz synchronous timer. The 32KHz synchronous timer is used to keep track
 * of time in addition to the 32KHz OS timer. Using only the 32KHz OS timer
 * on 1510 would be possible, but the timer would not be as accurate as
 * with the 32KHz synchronized timer.
 * ---------------------------------------------------------------------------
 */

/* 16xx specific defines */
#define OMAP1_32K_TIMER_BASE		0xfffb9000
#define OMAP1_32KSYNC_TIMER_BASE	0xfffbc400
#define OMAP1_32K_TIMER_CR		0x08
#define OMAP1_32K_TIMER_TVR		0x00
#define OMAP1_32K_TIMER_TCR		0x04

#define OMAP_32K_TICKS_PER_SEC		(32768)

/*
 * TRM says 1 / HZ = ( TVR + 1) / 32768, so TRV = (32768 / HZ) - 1
 * so with HZ = 128, TVR = 255.
 */
#define OMAP_32K_TIMER_TICK_PERIOD	((OMAP_32K_TICKS_PER_SEC / HZ) - 1)

#define JIFFIES_TO_HW_TICKS(nr_jiffies, clock_rate)			\
				(((nr_jiffies) * (clock_rate)) / HZ)

static inline void omap_32k_timer_write(int val, int reg)
{
	omap_writew(val, OMAP1_32K_TIMER_BASE + reg);
}

static inline unsigned long omap_32k_timer_read(int reg)
{
	return omap_readl(OMAP1_32K_TIMER_BASE + reg) & 0xffffff;
}

static inline void omap_32k_timer_start(unsigned long load_val)
{
	if (!load_val)
		load_val = 1;
	omap_32k_timer_write(load_val, OMAP1_32K_TIMER_TVR);
	omap_32k_timer_write(0x0f, OMAP1_32K_TIMER_CR);
}

static inline void omap_32k_timer_stop(void)
{
	omap_32k_timer_write(0x0, OMAP1_32K_TIMER_CR);
}

#define omap_32k_timer_ack_irq()

static int omap_32k_timer_set_next_event(unsigned long delta,
					 struct clock_event_device *dev)
{
	omap_32k_timer_start(delta);

	return 0;
}

static void omap_32k_timer_set_mode(enum clock_event_mode mode,
				    struct clock_event_device *evt)
{
	omap_32k_timer_stop();

	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		omap_32k_timer_start(OMAP_32K_TIMER_TICK_PERIOD);
		break;
	case CLOCK_EVT_MODE_ONESHOT:
	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_SHUTDOWN:
		break;
	case CLOCK_EVT_MODE_RESUME:
		break;
	}
}

static struct clock_event_device clockevent_32k_timer = {
	.name		= "32k-timer",
	.features       = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT,
	.shift		= 32,
	.set_next_event	= omap_32k_timer_set_next_event,
	.set_mode	= omap_32k_timer_set_mode,
};

static irqreturn_t omap_32k_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *evt = &clockevent_32k_timer;
	omap_32k_timer_ack_irq();

	evt->event_handler(evt);

	return IRQ_HANDLED;
}

static struct irqaction omap_32k_timer_irq = {
	.name		= "32KHz timer",
	.flags		= IRQF_DISABLED | IRQF_TIMER | IRQF_IRQPOLL,
	.handler	= omap_32k_timer_interrupt,
};

static __init void omap_init_32k_timer(void)
{
	setup_irq(INT_OS_TIMER, &omap_32k_timer_irq);

	clockevent_32k_timer.mult = div_sc(OMAP_32K_TICKS_PER_SEC,
					   NSEC_PER_SEC,
					   clockevent_32k_timer.shift);
	clockevent_32k_timer.max_delta_ns =
		clockevent_delta2ns(0xfffffffe, &clockevent_32k_timer);
	clockevent_32k_timer.min_delta_ns =
		clockevent_delta2ns(1, &clockevent_32k_timer);

	clockevent_32k_timer.cpumask = cpumask_of(0);
	clockevents_register_device(&clockevent_32k_timer);
}

/*
 * ---------------------------------------------------------------------------
 * Timer initialization
 * ---------------------------------------------------------------------------
 */
int __init omap_32k_timer_init(void)
{
	int ret = -ENODEV;

	if (cpu_is_omap16xx()) {
		void __iomem *base;
		struct clk *sync32k_ick;

		base = ioremap(OMAP1_32KSYNC_TIMER_BASE, SZ_1K);
		if (!base) {
			pr_err("32k_counter: failed to map base addr\n");
			return -ENODEV;
		}

		sync32k_ick = clk_get(NULL, "omap_32ksync_ick");
		if (!IS_ERR(sync32k_ick))
			clk_enable(sync32k_ick);

		ret = omap_init_clocksource_32k(base);
	}

	if (!ret)
		omap_init_32k_timer();

	return ret;
}
