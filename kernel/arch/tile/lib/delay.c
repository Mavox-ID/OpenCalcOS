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
#include <beep/delay.h>
#include <beep/thread_info.h>
#include <asm/timex.h>

void __udelay(unsigned long usecs)
{
	if (usecs > ULONG_MAX / 1000) {
		WARN_ON_ONCE(usecs > ULONG_MAX / 1000);
		usecs = ULONG_MAX / 1000;
	}
	__ndelay(usecs * 1000);
}
EXPORT_SYMBOL(__udelay);

void __ndelay(unsigned long nsecs)
{
	cycles_t target = get_cycles();
	target += ns2cycles(nsecs);
	while (get_cycles() < target)
		cpu_relax();
}
EXPORT_SYMBOL(__ndelay);

void __delay(unsigned long cycles)
{
	cycles_t target = get_cycles() + cycles;
	while (get_cycles() < target)
		cpu_relax();
}
EXPORT_SYMBOL(__delay);
