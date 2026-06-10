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
#ifndef __ASM_ARM_LOCALTIMER_H
#define __ASM_ARM_LOCALTIMER_H

#include <beep/errno.h>

struct clock_event_device;

struct local_timer_ops {
	int  (*setup)(struct clock_event_device *);
	void (*stop)(struct clock_event_device *);
};

#ifdef CONFIG_LOCAL_TIMERS
/*
 * Register a local timer driver
 */
int local_timer_register(struct local_timer_ops *);
#else
static inline int local_timer_register(struct local_timer_ops *ops)
{
	return -ENXIO;
}
#endif

#endif
