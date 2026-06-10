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
#ifndef __ASM_RC32434_TIMER_H
#define __ASM_RC32434_TIMER_H

#include <asm/mach-rc32434/rb.h>

#define TIMER0_BASE_ADDR		0x18028000
#define TIMER_COUNT			3

struct timer_counter {
	u32 count;
	u32 compare;
	u32 ctc;		/*use CTC_ */
};

struct timer {
	struct timer_counter tim[TIMER_COUNT];
	u32 rcount;	/* use RCOUNT_ */
	u32 rcompare;	/* use RCOMPARE_ */
	u32 rtc;	/* use RTC_ */
};

#define RC32434_CTC_EN_BIT		0
#define RC32434_CTC_TO_BIT		1

/* Real time clock registers */
#define RC32434_RTC_MSK(x)              BIT_TO_MASK(x)
#define RC32434_RTC_CE_BIT              0
#define RC32434_RTC_TO_BIT              1
#define RC32434_RTC_RQE_BIT             2

/* Counter registers */
#define RC32434_RCOUNT_BIT              0
#define RC32434_RCOUNT_MSK              0x0000ffff
#define RC32434_RCOMP_BIT               0
#define RC32434_RCOMP_MSK               0x0000ffff

#endif  /* __ASM_RC32434_TIMER_H */
