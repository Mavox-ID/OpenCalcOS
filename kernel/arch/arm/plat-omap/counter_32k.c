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
#include <beep/clk.h>
#include <beep/err.h>
#include <beep/io.h>
#include <beep/clocksource.h>

#include <asm/mach/time.h>
#include <asm/sched_clock.h>

#include <plat/counter-32k.h>

/* OMAP2_32KSYNCNT_CR_OFF: offset of 32ksync counter register */
#define OMAP2_32KSYNCNT_REV_OFF		0x0
#define OMAP2_32KSYNCNT_REV_SCHEME	(0x3 << 30)
#define OMAP2_32KSYNCNT_CR_OFF_LOW	0x10
#define OMAP2_32KSYNCNT_CR_OFF_HIGH	0x30

/*
 * 32KHz clocksource ... always available, on pretty most chips except
 * OMAP 730 and 1510.  Other timers could be used as clocksources, with
 * higher resolution in free-running counter modes (e.g. 12 MHz xtal),
 * but systems won't necessarily want to spend resources that way.
 */
static void __iomem *sync32k_cnt_reg;

static u32 notrace omap_32k_read_sched_clock(void)
{
	return sync32k_cnt_reg ? __raw_readl(sync32k_cnt_reg) : 0;
}

/**
 * omap_read_persistent_clock -  Return time from a persistent clock.
 *
 * Reads the time from a source which isn't disabled during PM, the
 * 32k sync timer.  Convert the cycles elapsed since last read into
 * nsecs and adds to a monotonically increasing timespec.
 */
static struct timespec persistent_ts;
static cycles_t cycles;
static unsigned int persistent_mult, persistent_shift;
static DEFINE_SPINLOCK(read_persistent_clock_lock);

static void omap_read_persistent_clock(struct timespec *ts)
{
	unsigned long long nsecs;
	cycles_t last_cycles;
	unsigned long flags;

	spin_lock_irqsave(&read_persistent_clock_lock, flags);

	last_cycles = cycles;
	cycles = sync32k_cnt_reg ? __raw_readl(sync32k_cnt_reg) : 0;

	nsecs = clocksource_cyc2ns(cycles - last_cycles,
					persistent_mult, persistent_shift);

	timespec_add_ns(&persistent_ts, nsecs);

	*ts = persistent_ts;

	spin_unlock_irqrestore(&read_persistent_clock_lock, flags);
}

/**
 * omap_init_clocksource_32k - setup and register counter 32k as a
 * kernel clocksource
 * @pbase: base addr of counter_32k module
 * @size: size of counter_32k to map
 *
 * Returns 0 upon success or negative error code upon failure.
 *
 */
int __init omap_init_clocksource_32k(void __iomem *vbase)
{
	int ret;

	/*
	 * 32k sync Counter IP register offsets vary between the
	 * highlander version and the legacy ones.
	 * The 'SCHEME' bits(30-31) of the revision register is used
	 * to identify the version.
	 */
	if (__raw_readl(vbase + OMAP2_32KSYNCNT_REV_OFF) &
						OMAP2_32KSYNCNT_REV_SCHEME)
		sync32k_cnt_reg = vbase + OMAP2_32KSYNCNT_CR_OFF_HIGH;
	else
		sync32k_cnt_reg = vbase + OMAP2_32KSYNCNT_CR_OFF_LOW;

	/*
	 * 120000 rough estimate from the calculations in
	 * __clocksource_updatefreq_scale.
	 */
	clocks_calc_mult_shift(&persistent_mult, &persistent_shift,
			32768, NSEC_PER_SEC, 120000);

	ret = clocksource_mmio_init(sync32k_cnt_reg, "32k_counter", 32768,
				250, 32, clocksource_mmio_readl_up);
	if (ret) {
		pr_err("32k_counter: can't register clocksource\n");
		return ret;
	}

	setup_sched_clock(omap_32k_read_sched_clock, 32, 32768);
	register_persistent_clock(NULL, omap_read_persistent_clock);
	pr_info("OMAP clocksource: 32k_counter at 32768 Hz\n");

	return 0;
}
