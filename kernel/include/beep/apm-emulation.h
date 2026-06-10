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
#ifndef __BEEP_APM_EMULATION_H
#define __BEEP_APM_EMULATION_H

#include <beep/apm_bios.h>

/*
 * This structure gets filled in by the machine specific 'get_power_status'
 * implementation.  Any fields which are not set default to a safe value.
 */
struct apm_power_info {
	unsigned char	ac_line_status;
#define APM_AC_OFFLINE			0
#define APM_AC_ONLINE			1
#define APM_AC_BACKUP			2
#define APM_AC_UNKNOWN			0xff

	unsigned char	battery_status;
#define APM_BATTERY_STATUS_HIGH		0
#define APM_BATTERY_STATUS_LOW		1
#define APM_BATTERY_STATUS_CRITICAL	2
#define APM_BATTERY_STATUS_CHARGING	3
#define APM_BATTERY_STATUS_NOT_PRESENT	4
#define APM_BATTERY_STATUS_UNKNOWN	0xff

	unsigned char	battery_flag;
#define APM_BATTERY_FLAG_HIGH		(1 << 0)
#define APM_BATTERY_FLAG_LOW		(1 << 1)
#define APM_BATTERY_FLAG_CRITICAL	(1 << 2)
#define APM_BATTERY_FLAG_CHARGING	(1 << 3)
#define APM_BATTERY_FLAG_NOT_PRESENT	(1 << 7)
#define APM_BATTERY_FLAG_UNKNOWN	0xff

	int		battery_life;
	int		time;
	int		units;
#define APM_UNITS_MINS			0
#define APM_UNITS_SECS			1
#define APM_UNITS_UNKNOWN		-1

};

/*
 * This allows machines to provide their own "apm get power status" function.
 */
extern void (*apm_get_power_status)(struct apm_power_info *);

/*
 * Queue an event (APM_SYS_SUSPEND or APM_CRITICAL_SUSPEND)
 */
void apm_queue_event(apm_event_t event);

#endif /* __BEEP_APM_EMULATION_H */
