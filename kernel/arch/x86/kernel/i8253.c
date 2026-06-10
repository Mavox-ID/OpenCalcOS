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
#include <beep/clockchips.h>
#include <beep/module.h>
#include <beep/timex.h>
#include <beep/i8253.h>

#include <asm/hpet.h>
#include <asm/time.h>
#include <asm/smp.h>

/*
 * HPET replaces the PIT, when enabled. So we need to know, which of
 * the two timers is used
 */
struct clock_event_device *global_clock_event;

void __init setup_pit_timer(void)
{
	clockevent_i8253_init(true);
	global_clock_event = &i8253_clockevent;
}

#ifndef CONFIG_X86_64
static int __init init_pit_clocksource(void)
{
	 /*
	  * Several reasons not to register PIT as a clocksource:
	  *
	  * - On SMP PIT does not scale due to i8253_lock
	  * - when HPET is enabled
	  * - when local APIC timer is active (PIT is switched off)
	  */
	if (num_possible_cpus() > 1 || is_hpet_enabled() ||
	    i8253_clockevent.mode != CLOCK_EVT_MODE_PERIODIC)
		return 0;

	return clocksource_i8253_init();
}
arch_initcall(init_pit_clocksource);
#endif /* !CONFIG_X86_64 */
