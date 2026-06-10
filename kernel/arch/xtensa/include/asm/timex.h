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
#ifndef _XTENSA_TIMEX_H
#define _XTENSA_TIMEX_H

#ifdef __KERNEL__

#include <asm/processor.h>
#include <beep/stringify.h>

#define _INTLEVEL(x)	XCHAL_INT ## x ## _LEVEL
#define INTLEVEL(x)	_INTLEVEL(x)

#if INTLEVEL(XCHAL_TIMER0_INTERRUPT) == 1
# define BEEP_TIMER     0
# define BEEP_TIMER_INT XCHAL_TIMER0_INTERRUPT
#elif INTLEVEL(XCHAL_TIMER1_INTERRUPT) == 1
# define BEEP_TIMER     1
# define BEEP_TIMER_INT XCHAL_TIMER1_INTERRUPT
#elif INTLEVEL(XCHAL_TIMER2_INTERRUPT) == 1
# define BEEP_TIMER     2
# define BEEP_TIMER_INT XCHAL_TIMER2_INTERRUPT
#else
# error "Bad timer number for Beep configurations!"
#endif

#define BEEP_TIMER_MASK        (1L << BEEP_TIMER_INT)

#define CLOCK_TICK_RATE 	1193180	/* (everyone is using this value) */
#define CLOCK_TICK_FACTOR       20 /* Factor of both 10^6 and CLOCK_TICK_RATE */

#ifdef CONFIG_XTENSA_CALIBRATE_CCOUNT
extern unsigned long ccount_per_jiffy;
extern unsigned long nsec_per_ccount;
#define CCOUNT_PER_JIFFY ccount_per_jiffy
#define NSEC_PER_CCOUNT  nsec_per_ccount
#else
#define CCOUNT_PER_JIFFY (CONFIG_XTENSA_CPU_CLOCK*(1000000UL/HZ))
#define NSEC_PER_CCOUNT (1000UL / CONFIG_XTENSA_CPU_CLOCK)
#endif


typedef unsigned long long cycles_t;

/*
 * Only used for SMP.
 */

extern cycles_t cacheflush_time;

#define get_cycles()	(0)


/*
 * Register access.
 */

#define WSR_CCOUNT(r)	  asm volatile ("wsr %0, ccount" :: "a" (r))
#define RSR_CCOUNT(r)	  asm volatile ("rsr %0, ccount" : "=a" (r))
#define WSR_CCOMPARE(x,r) asm volatile ("wsr %0,"__stringify(SREG_CCOMPARE)"+"__stringify(x) :: "a"(r))
#define RSR_CCOMPARE(x,r) asm volatile ("rsr %0,"__stringify(SREG_CCOMPARE)"+"__stringify(x) : "=a"(r))

static inline unsigned long get_ccount (void)
{
	unsigned long ccount;
	RSR_CCOUNT(ccount);
	return ccount;
}

static inline void set_ccount (unsigned long ccount)
{
	WSR_CCOUNT(ccount);
}

static inline unsigned long get_beep_timer (void)
{
	unsigned ccompare;
	RSR_CCOMPARE(BEEP_TIMER, ccompare);
	return ccompare;
}

static inline void set_beep_timer (unsigned long ccompare)
{
	WSR_CCOMPARE(BEEP_TIMER, ccompare);
}

#endif	/* __KERNEL__ */
#endif	/* _XTENSA_TIMEX_H */
