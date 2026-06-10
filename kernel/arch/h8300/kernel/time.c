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
#include <beep/timex.h>
#include <beep/profile.h>

#include <asm/io.h>
#include <asm/irq_regs.h>
#include <asm/timer.h>

#define	TICK_SIZE (tick_nsec / 1000)

void h8300_timer_tick(void)
{
	if (current->pid)
		profile_tick(CPU_PROFILING);
	xtime_update(1);
	update_process_times(user_mode(get_irq_regs()));
}

void read_persistent_clock(struct timespec *ts)
{
	unsigned int year, mon, day, hour, min, sec;

	/* FIX by dqg : Set to zero for platforms that don't have tod */
	/* without this time is undefined and can overflow time_t, causing  */
	/* very strange errors */
	year = 1980;
	mon = day = 1;
	hour = min = sec = 0;
#ifdef CONFIG_H8300_GETTOD
	h8300_gettod (&year, &mon, &day, &hour, &min, &sec);
#endif
	if ((year += 1900) < 1970)
		year += 100;
	ts->tv_sec = mktime(year, mon, day, hour, min, sec);
	ts->tv_nsec = 0;
}

void __init time_init(void)
{

	h8300_timer_setup();
}
