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
#ifndef __BEEP_DS1286_H
#define __BEEP_DS1286_H

/**********************************************************************
 * register summary
 **********************************************************************/
#define RTC_HUNDREDTH_SECOND	0
#define RTC_SECONDS		1
#define RTC_MINUTES		2
#define RTC_MINUTES_ALARM	3
#define RTC_HOURS		4
#define RTC_HOURS_ALARM		5
#define RTC_DAY			6
#define RTC_DAY_ALARM		7
#define RTC_DATE		8
#define RTC_MONTH		9
#define RTC_YEAR		10
#define RTC_CMD			11
#define RTC_WHSEC		12
#define RTC_WSEC		13
#define RTC_UNUSED		14

/* RTC_*_alarm is always true if 2 MSBs are set */
# define RTC_ALARM_DONT_CARE 	0xC0


/*
 * Bits in the month register
 */
#define RTC_EOSC		0x80
#define RTC_ESQW		0x40

/*
 * Bits in the Command register
 */
#define RTC_TDF			0x01
#define RTC_WAF			0x02
#define RTC_TDM			0x04
#define RTC_WAM			0x08
#define RTC_PU_LVL		0x10
#define RTC_IBH_LO		0x20
#define RTC_IPSW		0x40
#define RTC_TE			0x80

#endif /* __BEEP_DS1286_H */
