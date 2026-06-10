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
#ifndef _SPARC_TIMER_H
#define _SPARC_TIMER_H

#include <beep/clocksource.h>
#include <beep/irqreturn.h>

#include <asm-generic/percpu.h>

#include <asm/cpu_type.h>  /* For SUN4M_NCPUS */

#define SBUS_CLOCK_RATE   2000000 /* 2MHz */
#define TIMER_VALUE_SHIFT 9
#define TIMER_VALUE_MASK  0x3fffff
#define TIMER_LIMIT_BIT   (1 << 31)  /* Bit 31 in Counter-Timer register */

/* The counter timer register has the value offset by 9 bits.
 * From sun4m manual:
 * When a counter reaches the value in the corresponding limit register,
 * the Limit bit is set and the counter is set to 500 nS (i.e. 0x00000200).
 *
 * To compensate for this add one to the value.
 */
static inline unsigned int timer_value(unsigned int value)
{
	return (value + 1) << TIMER_VALUE_SHIFT;
}

extern __volatile__ unsigned int *master_l10_counter;

extern irqreturn_t notrace timer_interrupt(int dummy, void *dev_id);

#ifdef CONFIG_SMP
DECLARE_PER_CPU(struct clock_event_device, sparc32_clockevent);
extern void register_percpu_ce(int cpu);
#endif

#endif /* !(_SPARC_TIMER_H) */
