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
#ifndef _BEEP_RTC_M48T59_H_
#define _BEEP_RTC_M48T59_H_

/*
 * M48T59 Register Offset
 */
#define M48T59_YEAR		0xf
#define M48T59_MONTH		0xe
#define M48T59_MDAY		0xd	/* Day of Month */
#define M48T59_WDAY		0xc	/* Day of Week */
#define M48T59_WDAY_CB			0x20	/* Century Bit */
#define M48T59_WDAY_CEB			0x10	/* Century Enable Bit */
#define M48T59_HOUR		0xb
#define M48T59_MIN		0xa
#define M48T59_SEC		0x9
#define M48T59_CNTL		0x8
#define M48T59_CNTL_READ		0x40
#define M48T59_CNTL_WRITE		0x80
#define M48T59_WATCHDOG		0x7
#define M48T59_INTR		0x6
#define M48T59_INTR_AFE			0x80	/* Alarm Interrupt Enable */
#define M48T59_INTR_ABE			0x20
#define M48T59_ALARM_DATE	0x5
#define M48T59_ALARM_HOUR	0x4
#define M48T59_ALARM_MIN	0x3
#define M48T59_ALARM_SEC	0x2
#define M48T59_UNUSED		0x1
#define M48T59_FLAGS		0x0
#define M48T59_FLAGS_WDT		0x80	/* watchdog timer expired */
#define M48T59_FLAGS_AF			0x40	/* alarm */
#define M48T59_FLAGS_BF			0x10	/* low battery */

#define M48T59RTC_TYPE_M48T59	0 /* to keep compatibility */
#define M48T59RTC_TYPE_M48T02	1
#define M48T59RTC_TYPE_M48T08	2

struct m48t59_plat_data {
	/* The method to access M48T59 registers */
	void (*write_byte)(struct device *dev, u32 ofs, u8 val);
	unsigned char (*read_byte)(struct device *dev, u32 ofs);

	int type; /* RTC model */

	/* ioaddr mapped externally */
	void __iomem *ioaddr;
	/* offset to RTC registers, automatically set according to the type */
	unsigned int offset;
};

#endif /* _BEEP_RTC_M48T59_H_ */
