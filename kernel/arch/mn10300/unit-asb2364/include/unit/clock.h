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
#ifndef _ASM_UNIT_CLOCK_H
#define _ASM_UNIT_CLOCK_H

#ifndef __ASSEMBLY__

#define MN10300_IOCLK		100000000UL		/* for DDR800 */
/*#define MN10300_IOCLK		83333333UL */		/* for DDR667 */
#define MN10300_IOBCLK		MN10300_IOCLK		/* IOBCLK is equal to IOCLK */

#endif /* !__ASSEMBLY__ */

#define MN10300_WDCLK		27000000UL

#endif /* _ASM_UNIT_CLOCK_H */
