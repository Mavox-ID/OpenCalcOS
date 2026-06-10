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
#include <hwregs/reg_map.h>
#include <hwregs/reg_rdwr.h>
#include <hwregs/timer_defs.h>
#include <beep/types.h>
#include <beep/delay.h>
#include <beep/module.h>

/*
 * On ETRAX FS, we can check the free-running read-only 100MHz timer
 * getting 32-bit 10ns precision, theoretically good for 42.94967295
 * seconds.  Unsigned arithmetic and careful expression handles
 * wrapping.
 */

void cris_delay10ns(u32 n10ns)
{
	u32 t0 = REG_RD(timer, regi_timer0, r_time);
	while (REG_RD(timer, regi_timer0, r_time) - t0 < n10ns)
		;
}
EXPORT_SYMBOL(cris_delay10ns);
