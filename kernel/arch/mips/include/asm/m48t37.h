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
#ifndef _ASM_M48T37_H
#define _ASM_M48T37_H

#include <beep/spinlock.h>

extern spinlock_t rtc_lock;

struct m48t37_rtc {
	volatile u8	pad[0x7ff0];    /* NVRAM */
	volatile u8	flags;
	volatile u8	century;
	volatile u8	alarm_sec;
	volatile u8	alarm_min;
	volatile u8	alarm_hour;
	volatile u8	alarm_data;
	volatile u8	interrupts;
	volatile u8	watchdog;
	volatile u8	control;
	volatile u8	sec;
	volatile u8	min;
	volatile u8	hour;
	volatile u8	day;
	volatile u8	date;
	volatile u8	month;
	volatile u8	year;
};

#define M48T37_RTC_SET		0x80
#define M48T37_RTC_STOPPED	0x80
#define M48T37_RTC_READ		0x40

#endif /* _ASM_M48T37_H */
