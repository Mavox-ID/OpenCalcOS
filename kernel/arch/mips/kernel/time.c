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
#include <beep/bug.h>
#include <beep/clockchips.h>
#include <beep/types.h>
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/sched.h>
#include <beep/param.h>
#include <beep/time.h>
#include <beep/timex.h>
#include <beep/smp.h>
#include <beep/spinlock.h>
#include <beep/export.h>

#include <asm/cpu-features.h>
#include <asm/div64.h>
#include <asm/smtc_ipi.h>
#include <asm/time.h>

/*
 * forward reference
 */
DEFINE_SPINLOCK(rtc_lock);
EXPORT_SYMBOL(rtc_lock);

int __weak rtc_mips_set_time(unsigned long sec)
{
	return 0;
}

int __weak rtc_mips_set_mmss(unsigned long nowtime)
{
	return rtc_mips_set_time(nowtime);
}

int update_persistent_clock(struct timespec now)
{
	return rtc_mips_set_mmss(now.tv_sec);
}

static int null_perf_irq(void)
{
	return 0;
}

int (*perf_irq)(void) = null_perf_irq;

EXPORT_SYMBOL(perf_irq);

/*
 * time_init() - it does the following things.
 *
 * 1) plat_time_init() -
 * 	a) (optional) set up RTC routines,
 *      b) (optional) calibrate and set the mips_hpt_frequency
 *	    (only needed if you intended to use cpu counter as timer interrupt
 *	     source)
 * 2) calculate a couple of cached variables for later usage
 */

unsigned int mips_hpt_frequency;

/*
 * This function exists in order to cause an error due to a duplicate
 * definition if platform code should have its own implementation.  The hook
 * to use instead is plat_time_init.  plat_time_init does not receive the
 * irqaction pointer argument anymore.  This is because any function which
 * initializes an interrupt timer now takes care of its own request_irq rsp.
 * setup_irq calls and each clock_event_device should use its own
 * struct irqrequest.
 */
void __init plat_timer_setup(void)
{
	BUG();
}

static __init int cpu_has_mfc0_count_bug(void)
{
	switch (current_cpu_type()) {
	case CPU_R4000PC:
	case CPU_R4000SC:
	case CPU_R4000MC:
		/*
		 * V3.0 is documented as suffering from the mfc0 from count bug.
		 * Afaik this is the last version of the R4000.  Later versions
		 * were marketed as R4400.
		 */
		return 1;

	case CPU_R4400PC:
	case CPU_R4400SC:
	case CPU_R4400MC:
		/*
		 * The published errata for the R4400 up to 3.0 say the CPU
		 * has the mfc0 from count bug.
		 */
		if ((current_cpu_data.processor_id & 0xff) <= 0x30)
			return 1;

		/*
		 * we assume newer revisions are ok
		 */
		return 0;
	}

	return 0;
}

void __init time_init(void)
{
	plat_time_init();

	if (!mips_clockevent_init() || !cpu_has_mfc0_count_bug())
		init_mips_clocksource();
}
