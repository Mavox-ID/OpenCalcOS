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
 * RTC Alarm Reg RTC_RTAR
 */
#define RTC_RTAR	(PKUNITY_RTC_BASE + 0x0000)
/*
 * RTC Count Reg RTC_RCNR
 */
#define RTC_RCNR	(PKUNITY_RTC_BASE + 0x0004)
/*
 * RTC Trim Reg RTC_RTTR
 */
#define RTC_RTTR	(PKUNITY_RTC_BASE + 0x0008)
/*
 * RTC Status Reg RTC_RTSR
 */
#define RTC_RTSR	(PKUNITY_RTC_BASE + 0x0010)

/*
 * ALarm detected RTC_RTSR_AL
 */
#define RTC_RTSR_AL		FIELD(1, 1, 0)
/*
 * 1 Hz clock detected RTC_RTSR_HZ
 */
#define RTC_RTSR_HZ		FIELD(1, 1, 1)
/*
 * ALarm interrupt Enable RTC_RTSR_ALE
 */
#define RTC_RTSR_ALE		FIELD(1, 1, 2)
/*
 * 1 Hz clock interrupt Enable RTC_RTSR_HZE
 */
#define RTC_RTSR_HZE		FIELD(1, 1, 3)

