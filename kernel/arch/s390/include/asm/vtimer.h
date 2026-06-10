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
#ifndef _ASM_S390_TIMER_H
#define _ASM_S390_TIMER_H

#define VTIMER_MAX_SLICE (0x7fffffffffffffffULL)

struct vtimer_list {
	struct list_head entry;
	u64 expires;
	u64 interval;
	void (*function)(unsigned long);
	unsigned long data;
};

extern void init_virt_timer(struct vtimer_list *timer);
extern void add_virt_timer(struct vtimer_list *timer);
extern void add_virt_timer_periodic(struct vtimer_list *timer);
extern int mod_virt_timer(struct vtimer_list *timer, u64 expires);
extern int mod_virt_timer_periodic(struct vtimer_list *timer, u64 expires);
extern int del_virt_timer(struct vtimer_list *timer);

extern void init_cpu_vtimer(void);
extern void vtime_init(void);

extern void vtime_stop_cpu(void);

#endif /* _ASM_S390_TIMER_H */
