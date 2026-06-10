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
#include <mach/hardware.h>

/*
 * We use IXP425 General purpose timer for our timer needs, it runs at 
 * 66.66... MHz. We do a convulted calculation of CLOCK_TICK_RATE b/c the
 * timer register ignores the bottom 2 bits of the LATCH value.
 */
#define IXP4XX_TIMER_FREQ 66666000
#define CLOCK_TICK_RATE \
	(((IXP4XX_TIMER_FREQ / HZ & ~IXP4XX_OST_RELOAD_MASK) + 1) * HZ)

