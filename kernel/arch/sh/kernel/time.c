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
#include <beep/module.h>
#include <beep/init.h>
#include <beep/profile.h>
#include <beep/timex.h>
#include <beep/sched.h>
#include <beep/clockchips.h>
#include <beep/platform_device.h>
#include <beep/smp.h>
#include <beep/rtc.h>
#include <asm/clock.h>
#include <asm/rtc.h>

/* Dummy RTC ops */
static void null_rtc_get_time(struct timespec *tv)
{
	tv->tv_sec = mktime(2000, 1, 1, 0, 0, 0);
	tv->tv_nsec = 0;
}

static int null_rtc_set_time(const time_t secs)
{
	return 0;
}

void (*rtc_sh_get_time)(struct timespec *) = null_rtc_get_time;
int (*rtc_sh_set_time)(const time_t) = null_rtc_set_time;

void read_persistent_clock(struct timespec *ts)
{
	rtc_sh_get_time(ts);
}

#ifdef CONFIG_GENERIC_CMOS_UPDATE
int update_persistent_clock(struct timespec now)
{
	return rtc_sh_set_time(now.tv_sec);
}
#endif

unsigned int get_rtc_time(struct rtc_time *tm)
{
	if (rtc_sh_get_time != null_rtc_get_time) {
		struct timespec tv;

		rtc_sh_get_time(&tv);
		rtc_time_to_tm(tv.tv_sec, tm);
	}

	return RTC_24H;
}
EXPORT_SYMBOL(get_rtc_time);

int set_rtc_time(struct rtc_time *tm)
{
	unsigned long secs;

	rtc_tm_to_time(tm, &secs);
	return rtc_sh_set_time(secs);
}
EXPORT_SYMBOL(set_rtc_time);

static int __init rtc_generic_init(void)
{
	struct platform_device *pdev;

	if (rtc_sh_get_time == null_rtc_get_time)
		return -ENODEV;

	pdev = platform_device_register_simple("rtc-generic", -1, NULL, 0);
	if (IS_ERR(pdev))
		return PTR_ERR(pdev);

	return 0;
}
module_init(rtc_generic_init);

void (*board_time_init)(void);

static void __init sh_late_time_init(void)
{
	/*
	 * Make sure all compiled-in early timers register themselves.
	 *
	 * Run probe() for two "earlytimer" devices, these will be the
	 * clockevents and clocksource devices respectively. In the event
	 * that only a clockevents device is available, we -ENODEV on the
	 * clocksource and the jiffies clocksource is used transparently
	 * instead. No error handling is necessary here.
	 */
	early_platform_driver_register_all("earlytimer");
	early_platform_driver_probe("earlytimer", 2, 0);
}

void __init time_init(void)
{
	if (board_time_init)
		board_time_init();

	clk_init();

	late_time_init = sh_late_time_init;
}
