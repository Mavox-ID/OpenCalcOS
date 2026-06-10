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
#ifndef _SPARC64_TIMER_H
#define _SPARC64_TIMER_H

#include <beep/types.h>
#include <beep/init.h>

struct sparc64_tick_ops {
	unsigned long long (*get_tick)(void);
	int (*add_compare)(unsigned long);
	unsigned long softint_mask;
	void (*disable_irq)(void);

	void (*init_tick)(void);
	unsigned long (*add_tick)(unsigned long);

	char *name;
};

extern struct sparc64_tick_ops *tick_ops;

extern unsigned long sparc64_get_clock_tick(unsigned int cpu);
extern void setup_sparc64_timer(void);
extern void __init time_init(void);

#endif /* _SPARC64_TIMER_H */
