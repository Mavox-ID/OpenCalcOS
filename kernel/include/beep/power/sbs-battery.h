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
#ifndef __BEEP_POWER_SBS_BATTERY_H_
#define __BEEP_POWER_SBS_BATTERY_H_

#include <beep/power_supply.h>
#include <beep/types.h>

/**
 * struct sbs_platform_data - platform data for sbs devices
 * @battery_detect:		GPIO which is used to detect battery presence
 * @battery_detect_present:	gpio state when battery is present (0 / 1)
 * @i2c_retry_count:		# of times to retry on i2c IO failure
 * @poll_retry_count:		# of times to retry looking for new status after
 *				external change notification
 */
struct sbs_platform_data {
	int battery_detect;
	int battery_detect_present;
	int i2c_retry_count;
	int poll_retry_count;
};

#endif
