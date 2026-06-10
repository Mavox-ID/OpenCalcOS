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
/*
 * This file contains definitions for accessing a platform supported high resolution
 * clock. The clock is monitonically increasing and can be accessed from any node
 * in the system. The clock is synchronized across nodes - all nodes see the
 * same value.
 * 
 *	RTC_COUNTER_ADDR - contains the address of the counter 
 *
 */

#ifndef _ASM_IA64_SN_CLKSUPPORT_H
#define _ASM_IA64_SN_CLKSUPPORT_H

extern unsigned long sn_rtc_cycles_per_second;

#define RTC_COUNTER_ADDR	((long *)LOCAL_MMR_ADDR(SH_RTC))

#define rtc_time()		(*RTC_COUNTER_ADDR)

#endif /* _ASM_IA64_SN_CLKSUPPORT_H */
