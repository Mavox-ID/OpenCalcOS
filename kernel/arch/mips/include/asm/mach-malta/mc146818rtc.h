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
#ifndef __ASM_MACH_MALTA_MC146818RTC_H
#define __ASM_MACH_MALTA_MC146818RTC_H

#include <asm/io.h>
#include <asm/mips-boards/generic.h>
#include <asm/mips-boards/malta.h>

#define RTC_PORT(x)	(0x70 + (x))
#define RTC_IRQ		8

static inline unsigned char CMOS_READ(unsigned long addr)
{
	outb(addr, MALTA_RTC_ADR_REG);
	return inb(MALTA_RTC_DAT_REG);
}

static inline void CMOS_WRITE(unsigned char data, unsigned long addr)
{
	outb(addr, MALTA_RTC_ADR_REG);
	outb(data, MALTA_RTC_DAT_REG);
}

#define RTC_ALWAYS_BCD	0

#define mc146818_decode_year(year) ((year) < 70 ? (year) + 2000 : (year) + 1900)

#endif /* __ASM_MACH_MALTA_MC146818RTC_H */
