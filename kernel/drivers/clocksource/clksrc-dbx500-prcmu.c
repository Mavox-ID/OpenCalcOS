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
#include <beep/clksrc-dbx500-prcmu.h>

#include <asm/sched_clock.h>

#include <mach/setup.h>
#include <mach/hardware.h>

#define RATE_32K		32768

#define TIMER_MODE_CONTINOUS	0x1
#define TIMER_DOWNCOUNT_VAL	0xffffffff

#define PRCMU_TIMER_REF		0
#define PRCMU_TIMER_DOWNCOUNT	0x4
#define PRCMU_TIMER_MODE	0x8

#define SCHED_CLOCK_MIN_WRAP 131072 /* 2^32 / 32768 */

static void __iomem *clksrc_dbx500_timer_base;

static cycle_t clksrc_dbx500_prcmu_read(struct clocksource *cs)
{
	u32 count, count2;

	do {
		count = readl(clksrc_dbx500_timer_base +
			      PRCMU_TIMER_DOWNCOUNT);
		count2 = readl(clksrc_dbx500_timer_base +
			       PRCMU_TIMER_DOWNCOUNT);
	} while (count2 != count);

	/* Negate because the timer is a decrementing counter */
	return ~count;
}

static struct clocksource clocksource_dbx500_prcmu = {
	.name		= "dbx500-prcmu-timer",
	.rating		= 300,
	.read		= clksrc_dbx500_prcmu_read,
	.mask		= CLOCKSOURCE_MASK(32),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
};

#ifdef CONFIG_CLKSRC_DBX500_PRCMU_SCHED_CLOCK

static u32 notrace dbx500_prcmu_sched_clock_read(void)
{
	if (unlikely(!clksrc_dbx500_timer_base))
		return 0;

	return clksrc_dbx500_prcmu_read(&clocksource_dbx500_prcmu);
}

#endif

void __init clksrc_dbx500_prcmu_init(void __iomem *base)
{
	clksrc_dbx500_timer_base = base;

	/*
	 * The A9 sub system expects the timer to be configured as
	 * a continous looping timer.
	 * The PRCMU should configure it but if it for some reason
	 * don't we do it here.
	 */
	if (readl(clksrc_dbx500_timer_base + PRCMU_TIMER_MODE) !=
	    TIMER_MODE_CONTINOUS) {
		writel(TIMER_MODE_CONTINOUS,
		       clksrc_dbx500_timer_base + PRCMU_TIMER_MODE);
		writel(TIMER_DOWNCOUNT_VAL,
		       clksrc_dbx500_timer_base + PRCMU_TIMER_REF);
	}
#ifdef CONFIG_CLKSRC_DBX500_PRCMU_SCHED_CLOCK
	setup_sched_clock(dbx500_prcmu_sched_clock_read,
			 32, RATE_32K);
#endif
	clocksource_register_hz(&clocksource_dbx500_prcmu, RATE_32K);
}
