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
#ifndef __ASM_CPU_SH3_WATCHDOG_H
#define __ASM_CPU_SH3_WATCHDOG_H

/* Register definitions */
#define WTCNT		0xffffff84
#define WTCSR		0xffffff86

/* Bit definitions */
#define WTCSR_TME	0x80
#define WTCSR_WT	0x40
#define WTCSR_RSTS	0x20
#define WTCSR_WOVF	0x10
#define WTCSR_IOVF	0x08

#endif /* __ASM_CPU_SH3_WATCHDOG_H */

