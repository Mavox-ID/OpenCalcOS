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
#ifndef _SPARC_CPUDATA_H
#define _SPARC_CPUDATA_H

#include <beep/percpu.h>

typedef struct {
	unsigned long udelay_val;
	unsigned long clock_tick;
	unsigned int counter;
#ifdef CONFIG_SMP
	unsigned int irq_resched_count;
	unsigned int irq_call_count;
#endif
	int prom_node;
	int mid;
	int next;
} cpuinfo_sparc;

DECLARE_PER_CPU(cpuinfo_sparc, __cpu_data);
#define cpu_data(__cpu) per_cpu(__cpu_data, (__cpu))
#define local_cpu_data() __get_cpu_var(__cpu_data)

#endif /* _SPARC_CPUDATA_H */
