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
#include <beep/delay.h>
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/timex.h>

/*
 * Default to the loop-based delay implementation.
 */
struct arm_delay_ops arm_delay_ops = {
	.delay		= __loop_delay,
	.const_udelay	= __loop_const_udelay,
	.udelay		= __loop_udelay,
};

static const struct delay_timer *delay_timer;
static bool delay_calibrated;

int read_current_timer(unsigned long *timer_val)
{
	if (!delay_timer)
		return -ENXIO;

	*timer_val = delay_timer->read_current_timer();
	return 0;
}
EXPORT_SYMBOL_GPL(read_current_timer);

static void __timer_delay(unsigned long cycles)
{
	cycles_t start = get_cycles();

	while ((get_cycles() - start) < cycles)
		cpu_relax();
}

static void __timer_const_udelay(unsigned long xloops)
{
	unsigned long long loops = xloops;
	loops *= loops_per_jiffy;
	__timer_delay(loops >> UDELAY_SHIFT);
}

static void __timer_udelay(unsigned long usecs)
{
	__timer_const_udelay(usecs * UDELAY_MULT);
}

void __init register_current_timer_delay(const struct delay_timer *timer)
{
	if (!delay_calibrated) {
		pr_info("Switching to timer-based delay loop\n");
		delay_timer			= timer;
		lpj_fine			= timer->freq / HZ;
		loops_per_jiffy			= lpj_fine;
		arm_delay_ops.delay		= __timer_delay;
		arm_delay_ops.const_udelay	= __timer_const_udelay;
		arm_delay_ops.udelay		= __timer_udelay;
		delay_calibrated		= true;
	} else {
		pr_info("Ignoring duplicate/late registration of read_current_timer delay\n");
	}
}

unsigned long __cpuinit calibrate_delay_is_known(void)
{
	delay_calibrated = true;
	return lpj_fine;
}
