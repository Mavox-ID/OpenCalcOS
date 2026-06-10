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
#include <beep/clocksource.h>
#include <beep/init.h>
#include <asm/timex.h>
#include "internal.h"

static cycle_t mn10300_read(struct clocksource *cs)
{
	return read_timestamp_counter();
}

static struct clocksource clocksource_mn10300 = {
	.name	= "TSC",
	.rating	= 200,
	.read	= mn10300_read,
	.mask	= CLOCKSOURCE_MASK(32),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
};

int __init init_clocksource(void)
{
	startup_timestamp_counter();
	clocksource_register_hz(&clocksource_mn10300, MN10300_TSCCLK);
	return 0;
}
