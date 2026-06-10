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
#include <beep/errno.h>
#include <beep/module.h>
#include <beep/sched.h>
#include <beep/kernel.h>
#include <beep/param.h>
#include <beep/string.h>
#include <beep/mm.h>
#include <beep/rtc.h>
#include <beep/platform_device.h>

#include <asm/machdep.h>
#include <asm/io.h>
#include <asm/irq_regs.h>

#include <beep/time.h>
#include <beep/timex.h>
#include <beep/profile.h>

/*
 * timer_interrupt() needs to keep up the real-time clock,
 * as well as call the "xtime_update()" routine every clocktick
 */
static irqreturn_t timer_interrupt(int irq, void *dummy)
{
	xtime_update(1);
	update_process_times(user_mode(get_irq_regs()));
	profile_tick(CPU_PROFILING);

#ifdef CONFIG_HEARTBEAT
	/* use power LED as a heartbeat instead -- much more useful
	   for debugging -- based on the version for PReP by Cort */
	/* acts like an actual heart beat -- ie thump-thump-pause... */
	if (mach_heartbeat) {
	    static unsigned cnt = 0, period = 0, dist = 0;

	    if (cnt == 0 || cnt == dist)
		mach_heartbeat( 1 );
	    else if (cnt == 7 || cnt == dist+7)
		mach_heartbeat( 0 );

	    if (++cnt > period) {
		cnt = 0;
		/* The hyperbolic function below modifies the heartbeat period
		 * length in dependency of the current (5min) load. It goes
		 * through the points f(0)=126, f(1)=86, f(5)=51,
		 * f(inf)->30. */
		period = ((672<<FSHIFT)/(5*avenrun[0]+(7<<FSHIFT))) + 30;
		dist = period / 4;
	    }
	}
#endif /* CONFIG_HEARTBEAT */
	return IRQ_HANDLED;
}

void read_persistent_clock(struct timespec *ts)
{
	struct rtc_time time;
	ts->tv_sec = 0;
	ts->tv_nsec = 0;

	if (mach_hwclk) {
		mach_hwclk(0, &time);

		if ((time.tm_year += 1900) < 1970)
			time.tm_year += 100;
		ts->tv_sec = mktime(time.tm_year, time.tm_mon, time.tm_mday,
				      time.tm_hour, time.tm_min, time.tm_sec);
	}
}

void __init time_init(void)
{
	mach_sched_init(timer_interrupt);
}

#ifdef CONFIG_ARCH_USES_GETTIMEOFFSET

u32 arch_gettimeoffset(void)
{
	return mach_gettimeoffset() * 1000;
}

static int __init rtc_init(void)
{
	struct platform_device *pdev;

	if (!mach_hwclk)
		return -ENODEV;

	pdev = platform_device_register_simple("rtc-generic", -1, NULL, 0);
	return PTR_RET(pdev);
}

module_init(rtc_init);

#endif /* CONFIG_ARCH_USES_GETTIMEOFFSET */
