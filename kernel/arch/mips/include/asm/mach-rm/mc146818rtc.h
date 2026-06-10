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
#ifndef __ASM_MACH_RM_MC146818RTC_H
#define __ASM_MACH_RM_MC146818RTC_H

#ifdef CONFIG_CPU_BIG_ENDIAN
#define mc146818_decode_year(year) ((year) < 70 ? (year) + 2000 : (year) + 1900)
#else
#define mc146818_decode_year(year) ((year) + 1980)
#endif

#include_next <mc146818rtc.h>

#endif /* __ASM_MACH_RM_MC146818RTC_H */
