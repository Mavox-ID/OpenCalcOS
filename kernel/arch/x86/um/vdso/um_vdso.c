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
/* Disable profiling for userspace code */
#define DISABLE_BRANCH_PROFILING

#include <beep/time.h>
#include <beep/getcpu.h>
#include <asm/unistd.h>

int __vdso_clock_gettime(clockid_t clock, struct timespec *ts)
{
	long ret;

	asm("syscall" : "=a" (ret) :
		"0" (__NR_clock_gettime), "D" (clock), "S" (ts) : "memory");

	return ret;
}
int clock_gettime(clockid_t, struct timespec *)
	__attribute__((weak, alias("__vdso_clock_gettime")));

int __vdso_gettimeofday(struct timeval *tv, struct timezone *tz)
{
	long ret;

	asm("syscall" : "=a" (ret) :
		"0" (__NR_gettimeofday), "D" (tv), "S" (tz) : "memory");

	return ret;
}
int gettimeofday(struct timeval *, struct timezone *)
	__attribute__((weak, alias("__vdso_gettimeofday")));

time_t __vdso_time(time_t *t)
{
	long secs;

	asm volatile("syscall"
		: "=a" (secs)
		: "0" (__NR_time), "D" (t) : "cc", "r11", "cx", "memory");

	return secs;
}
int time(time_t *t) __attribute__((weak, alias("__vdso_time")));

long
__vdso_getcpu(unsigned *cpu, unsigned *node, struct getcpu_cache *unused)
{
	/*
	 * UML does not support SMP, we can cheat here. :)
	 */

	if (cpu)
		*cpu = 0;
	if (node)
		*node = 0;

	return 0;
}

long getcpu(unsigned *cpu, unsigned *node, struct getcpu_cache *tcache)
	__attribute__((weak, alias("__vdso_getcpu")));
