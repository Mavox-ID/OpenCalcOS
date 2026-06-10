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
#include <asm/trace_clock.h>
#include <asm/barrier.h>
#include <asm/msr.h>

/*
 * trace_clock_x86_tsc(): A clock that is just the cycle counter.
 *
 * Unlike the other clocks, this is not in nanoseconds.
 */
u64 notrace trace_clock_x86_tsc(void)
{
	u64 ret;

	rdtsc_barrier();
	rdtscll(ret);

	return ret;
}
