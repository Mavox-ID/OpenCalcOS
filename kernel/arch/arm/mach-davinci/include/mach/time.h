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
#ifndef __ARCH_ARM_MACH_DAVINCI_TIME_H
#define __ARCH_ARM_MACH_DAVINCI_TIME_H

#define DAVINCI_TIMER0_BASE		(IO_PHYS + 0x21400)
#define DAVINCI_TIMER1_BASE		(IO_PHYS + 0x21800)
#define DAVINCI_WDOG_BASE		(IO_PHYS + 0x21C00)

enum {
	T0_BOT,
	T0_TOP,
	T1_BOT,
	T1_TOP,
	NUM_TIMERS
};

#define IS_TIMER1(id)		(id & 0x2)
#define IS_TIMER0(id)		(!IS_TIMER1(id))
#define IS_TIMER_TOP(id)	((id & 0x1))
#define IS_TIMER_BOT(id)	(!IS_TIMER_TOP(id))

#define ID_TO_TIMER(id)		(IS_TIMER1(id) != 0)

extern struct davinci_timer_instance davinci_timer_instance[];

#endif /* __ARCH_ARM_MACH_DAVINCI_TIME_H */
