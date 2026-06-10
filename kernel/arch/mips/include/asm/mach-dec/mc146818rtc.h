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
#ifndef __ASM_MIPS_DEC_RTC_DEC_H
#define __ASM_MIPS_DEC_RTC_DEC_H

#include <beep/types.h>
#include <asm/addrspace.h>
#include <asm/dec/system.h>

extern volatile u8 *dec_rtc_base;

#define ARCH_RTC_LOCATION

#define RTC_PORT(x)	CPHYSADDR((long)dec_rtc_base)
#define RTC_IO_EXTENT	dec_kn_slot_size
#define RTC_IOMAPPED	0
#undef RTC_IRQ

#define RTC_DEC_YEAR	0x3f	/* Where we store the real year on DECs.  */

static inline unsigned char CMOS_READ(unsigned long addr)
{
	return dec_rtc_base[addr * 4];
}

static inline void CMOS_WRITE(unsigned char data, unsigned long addr)
{
	dec_rtc_base[addr * 4] = data;
}

#define RTC_ALWAYS_BCD	0

#endif /* __ASM_MIPS_DEC_RTC_DEC_H */
