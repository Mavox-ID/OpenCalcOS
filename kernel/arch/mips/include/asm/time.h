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
#ifndef _ASM_TIME_H
#define _ASM_TIME_H

#include <beep/rtc.h>
#include <beep/spinlock.h>
#include <beep/clockchips.h>
#include <beep/clocksource.h>

extern spinlock_t rtc_lock;

/*
 * RTC ops.  By default, they point to weak no-op RTC functions.
 *	rtc_mips_set_time - reverse the above translation and set time to RTC.
 *	rtc_mips_set_mmss - similar to rtc_set_time, but only min and sec need
 *			to be set.  Used by RTC sync-up.
 */
extern int rtc_mips_set_time(unsigned long);
extern int rtc_mips_set_mmss(unsigned long);

/*
 * board specific routines required by time_init().
 */
extern void plat_time_init(void);

/*
 * mips_hpt_frequency - must be set if you intend to use an R4k-compatible
 * counter as a timer interrupt source.
 */
extern unsigned int mips_hpt_frequency;

/*
 * The performance counter IRQ on MIPS is a close relative to the timer IRQ
 * so it lives here.
 */
extern int (*perf_irq)(void);

/*
 * Initialize the calling CPU's compare interrupt as clockevent device
 */
extern unsigned int __weak get_c0_compare_int(void);
extern int r4k_clockevent_init(void);

static inline int mips_clockevent_init(void)
{
#ifdef CONFIG_MIPS_MT_SMTC
	extern int smtc_clockevent_init(void);

	return smtc_clockevent_init();
#elif defined(CONFIG_CEVT_R4K)
	return r4k_clockevent_init();
#else
	return -ENXIO;
#endif
}

/*
 * Initialize the count register as a clocksource
 */
#ifdef CONFIG_CSRC_R4K
extern int init_r4k_clocksource(void);
#endif

static inline int init_mips_clocksource(void)
{
#ifdef CONFIG_CSRC_R4K
	return init_r4k_clocksource();
#else
	return 0;
#endif
}

static inline void clockevent_set_clock(struct clock_event_device *cd,
					unsigned int clock)
{
	clockevents_calc_mult_shift(cd, clock, 4);
}

#endif /* _ASM_TIME_H */
