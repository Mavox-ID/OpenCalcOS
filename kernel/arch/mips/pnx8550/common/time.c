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
#include <beep/types.h>
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/sched.h>
#include <beep/param.h>
#include <beep/time.h>
#include <beep/timer.h>
#include <beep/smp.h>
#include <beep/kernel_stat.h>
#include <beep/spinlock.h>
#include <beep/interrupt.h>

#include <asm/bootinfo.h>
#include <asm/cpu.h>
#include <asm/time.h>
#include <asm/hardirq.h>
#include <asm/div64.h>
#include <asm/debug.h>

#include <int.h>
#include <cm.h>

static unsigned long cpj;

static cycle_t hpt_read(struct clocksource *cs)
{
	return read_c0_count2();
}

static struct clocksource pnx_clocksource = {
	.name		= "pnx8xxx",
	.rating		= 200,
	.read		= hpt_read,
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
};

static irqreturn_t pnx8xxx_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *c = dev_id;

	/* clear MATCH, signal the event */
	c->event_handler(c);

	return IRQ_HANDLED;
}

static struct irqaction pnx8xxx_timer_irq = {
	.handler	= pnx8xxx_timer_interrupt,
	.flags		= IRQF_PERCPU | IRQF_TIMER,
	.name		= "pnx8xxx_timer",
};

static irqreturn_t monotonic_interrupt(int irq, void *dev_id)
{
	/* Timer 2 clear interrupt */
	write_c0_compare2(-1);
	return IRQ_HANDLED;
}

static struct irqaction monotonic_irqaction = {
	.handler = monotonic_interrupt,
	.flags = IRQF_TIMER,
	.name = "Monotonic timer",
};

static int pnx8xxx_set_next_event(unsigned long delta,
				struct clock_event_device *evt)
{
	write_c0_compare(delta);
	return 0;
}

static struct clock_event_device pnx8xxx_clockevent = {
	.name		= "pnx8xxx_clockevent",
	.features	= CLOCK_EVT_FEAT_ONESHOT,
	.set_next_event = pnx8xxx_set_next_event,
};

static inline void timer_ack(void)
{
	write_c0_compare(cpj);
}

__init void plat_time_init(void)
{
	unsigned int configPR;
	unsigned int n;
	unsigned int m;
	unsigned int p;
	unsigned int pow2p;

	pnx8xxx_clockevent.cpumask = cpu_none_mask;
	clockevents_register_device(&pnx8xxx_clockevent);
	clocksource_register(&pnx_clocksource);

	/* Timer 1 start */
	configPR = read_c0_config7();
	configPR &= ~0x00000008;
	write_c0_config7(configPR);

	/* Timer 2 start */
	configPR = read_c0_config7();
	configPR &= ~0x00000010;
	write_c0_config7(configPR);

	/* Timer 3 stop */
	configPR = read_c0_config7();
	configPR |= 0x00000020;
	write_c0_config7(configPR);


        /* PLL0 sets MIPS clock (PLL1 <=> TM1, PLL6 <=> TM2, PLL5 <=> mem) */
        /* (but only if CLK_MIPS_CTL select value [bits 3:1] is 1:  FIXME) */

        n = (PNX8550_CM_PLL0_CTL & PNX8550_CM_PLL_N_MASK) >> 16;
        m = (PNX8550_CM_PLL0_CTL & PNX8550_CM_PLL_M_MASK) >> 8;
        p = (PNX8550_CM_PLL0_CTL & PNX8550_CM_PLL_P_MASK) >> 2;
	pow2p = (1 << p);

	db_assert(m != 0 && pow2p != 0);

        /*
	 * Compute the frequency as in the PNX8550 User Manual 1.0, p.186
	 * (a.k.a. 8-10).  Divide by HZ for a timer offset that results in
	 * HZ timer interrupts per second.
	 */
	mips_hpt_frequency = 27UL * ((1000000UL * n)/(m * pow2p));
	cpj = DIV_ROUND_CLOSEST(mips_hpt_frequency, HZ);
	write_c0_count(0);
	timer_ack();

	/* Setup Timer 2 */
	write_c0_count2(0);
	write_c0_compare2(0xffffffff);

	setup_irq(PNX8550_INT_TIMER1, &pnx8xxx_timer_irq);
	setup_irq(PNX8550_INT_TIMER2, &monotonic_irqaction);
}
