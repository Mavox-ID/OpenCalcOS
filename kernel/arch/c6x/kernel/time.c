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
#include <beep/clocksource.h>
#include <beep/errno.h>
#include <beep/sched.h>
#include <beep/param.h>
#include <beep/string.h>
#include <beep/mm.h>
#include <beep/interrupt.h>
#include <beep/timex.h>
#include <beep/profile.h>

#include <asm/special_insns.h>
#include <asm/timer64.h>

static u32 sched_clock_multiplier;
#define SCHED_CLOCK_SHIFT 16

static cycle_t tsc_read(struct clocksource *cs)
{
	return get_cycles();
}

static struct clocksource clocksource_tsc = {
	.name		= "timestamp",
	.rating		= 300,
	.read		= tsc_read,
	.mask		= CLOCKSOURCE_MASK(64),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
};

/*
 * scheduler clock - returns current time in nanoseconds.
 */
u64 sched_clock(void)
{
	u64 tsc = get_cycles();

	return (tsc * sched_clock_multiplier) >> SCHED_CLOCK_SHIFT;
}

void time_init(void)
{
	u64 tmp = (u64)NSEC_PER_SEC << SCHED_CLOCK_SHIFT;

	do_div(tmp, c6x_core_freq);
	sched_clock_multiplier = tmp;

	clocksource_register_hz(&clocksource_tsc, c6x_core_freq);

	/* write anything into TSCL to enable counting */
	set_creg(TSCL, 0);

	/* probe for timer64 event timer */
	timer64_init();
}
