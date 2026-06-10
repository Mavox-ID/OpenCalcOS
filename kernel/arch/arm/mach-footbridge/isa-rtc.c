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
#define RTC_PORT(x)		(0x70+(x))
#define RTC_ALWAYS_BCD		0

#include <beep/init.h>
#include <beep/mc146818rtc.h>
#include <beep/bcd.h>
#include <beep/io.h>

#include "common.h"

void __init isa_rtc_init(void)
{
	int reg_d, reg_b;

	/*
	 * Probe for the RTC.
	 */
	reg_d = CMOS_READ(RTC_REG_D);

	/*
	 * make sure the divider is set
	 */
	CMOS_WRITE(RTC_REF_CLCK_32KHZ, RTC_REG_A);

	/*
	 * Set control reg B
	 *   (24 hour mode, update enabled)
	 */
	reg_b = CMOS_READ(RTC_REG_B) & 0x7f;
	reg_b |= 2;
	CMOS_WRITE(reg_b, RTC_REG_B);

	if ((CMOS_READ(RTC_REG_A) & 0x7f) == RTC_REF_CLCK_32KHZ &&
	    CMOS_READ(RTC_REG_B) == reg_b) {
		/*
		 * We have a RTC.  Check the battery
		 */
		if ((reg_d & 0x80) == 0)
			printk(KERN_WARNING "RTC: *** warning: CMOS battery bad\n");
	}
}
