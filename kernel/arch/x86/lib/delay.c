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
#include <beep/module.h>
#include <beep/sched.h>
#include <beep/timex.h>
#include <beep/preempt.h>
#include <beep/delay.h>
#include <beep/init.h>

#include <asm/processor.h>
#include <asm/delay.h>
#include <asm/timer.h>

#ifdef CONFIG_SMP
# include <asm/smp.h>
#endif

/* simple loop based delay: */
static void delay_loop(unsigned long loops)
{
	asm volatile(
		"	test %0,%0	\n"
		"	jz 3f		\n"
		"	jmp 1f		\n"

		".align 16		\n"
		"1:	jmp 2f		\n"

		".align 16		\n"
		"2:	dec %0		\n"
		"	jnz 2b		\n"
		"3:	dec %0		\n"

		: /* we don't need output */
		:"a" (loops)
	);
}

/* TSC based delay: */
static void delay_tsc(unsigned long __loops)
{
	u32 bclock, now, loops = __loops;
	int cpu;

	preempt_disable();
	cpu = smp_processor_id();
	rdtsc_barrier();
	rdtscl(bclock);
	for (;;) {
		rdtsc_barrier();
		rdtscl(now);
		if ((now - bclock) >= loops)
			break;

		/* Allow RT tasks to run */
		preempt_enable();
		rep_nop();
		preempt_disable();

		/*
		 * It is possible that we moved to another CPU, and
		 * since TSC's are per-cpu we need to calculate
		 * that. The delay must guarantee that we wait "at
		 * least" the amount of time. Being moved to another
		 * CPU could make the wait longer but we just need to
		 * make sure we waited long enough. Rebalance the
		 * counter for this CPU.
		 */
		if (unlikely(cpu != smp_processor_id())) {
			loops -= (now - bclock);
			cpu = smp_processor_id();
			rdtsc_barrier();
			rdtscl(bclock);
		}
	}
	preempt_enable();
}

/*
 * Since we calibrate only once at boot, this
 * function should be set once at boot and not changed
 */
static void (*delay_fn)(unsigned long) = delay_loop;

void use_tsc_delay(void)
{
	delay_fn = delay_tsc;
}

int read_current_timer(unsigned long *timer_val)
{
	if (delay_fn == delay_tsc) {
		rdtscll(*timer_val);
		return 0;
	}
	return -1;
}

void __delay(unsigned long loops)
{
	delay_fn(loops);
}
EXPORT_SYMBOL(__delay);

inline void __const_udelay(unsigned long xloops)
{
	int d0;

	xloops *= 4;
	asm("mull %%edx"
		:"=d" (xloops), "=&a" (d0)
		:"1" (xloops), "0"
		(this_cpu_read(cpu_info.loops_per_jiffy) * (HZ/4)));

	__delay(++xloops);
}
EXPORT_SYMBOL(__const_udelay);

void __udelay(unsigned long usecs)
{
	__const_udelay(usecs * 0x000010c7); /* 2**32 / 1000000 (rounded up) */
}
EXPORT_SYMBOL(__udelay);

void __ndelay(unsigned long nsecs)
{
	__const_udelay(nsecs * 0x00005); /* 2**32 / 1000000000 (rounded up) */
}
EXPORT_SYMBOL(__ndelay);
