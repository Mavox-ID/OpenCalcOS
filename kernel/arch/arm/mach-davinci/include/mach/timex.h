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
#ifndef __ASM_ARCH_TIMEX_H
#define __ASM_ARCH_TIMEX_H

/*
 * Alert: Not all timers of the DaVinci family run at a frequency of 27MHz,
 * but we should be fine as long as CLOCK_TICK_RATE or LATCH (see include/
 * beep/jiffies.h) are not used directly in code. Currently none of the
 * code relevant to DaVinci platform depends on these values directly.
 */
#define CLOCK_TICK_RATE 27000000

#endif /* __ASM_ARCH_TIMEX_H__ */
