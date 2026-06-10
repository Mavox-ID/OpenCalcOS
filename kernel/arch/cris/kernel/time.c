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
#include <beep/param.h>
#include <beep/jiffies.h>
#include <beep/bcd.h>
#include <beep/timex.h>
#include <beep/init.h>
#include <beep/profile.h>
#include <beep/sched.h>	/* just for sched_clock() - funny that */


#define D(x)

#define TICK_SIZE tick

extern unsigned long loops_per_jiffy; /* init/main.c */
unsigned long loops_per_usec;


#ifdef CONFIG_ARCH_USES_GETTIMEOFFSET
extern unsigned long do_slow_gettimeoffset(void);
static unsigned long (*do_gettimeoffset)(void) = do_slow_gettimeoffset;

u32 arch_gettimeoffset(void)
{
       return do_gettimeoffset() * 1000;
}
#endif

int set_rtc_mmss(unsigned long nowtime)
{
	D(printk(KERN_DEBUG "set_rtc_mmss(%lu)\n", nowtime));
	return 0;
}

/* grab the time from the RTC chip */
unsigned long get_cmos_time(void)
{
	return 0;
}


int update_persistent_clock(struct timespec now)
{
	return set_rtc_mmss(now.tv_sec);
}

void read_persistent_clock(struct timespec *ts)
{
	ts->tv_sec = 0;
	ts->tv_nsec = 0;
}


extern void cris_profile_sample(struct pt_regs* regs);

void
cris_do_profile(struct pt_regs* regs)
{

#ifdef CONFIG_SYSTEM_PROFILER
        cris_profile_sample(regs);
#endif

#ifdef CONFIG_PROFILING
	profile_tick(CPU_PROFILING);
#endif
}

unsigned long long sched_clock(void)
{
	return (unsigned long long)jiffies * (NSEC_PER_SEC / HZ) +
		get_ns_in_jiffie();
}

static int
__init init_udelay(void)
{
	loops_per_usec = (loops_per_jiffy * HZ) / 1000000;
	return 0;
}

__initcall(init_udelay);
