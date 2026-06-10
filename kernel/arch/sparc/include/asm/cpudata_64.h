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
#ifndef _SPARC64_CPUDATA_H
#define _SPARC64_CPUDATA_H

#ifndef __ASSEMBLY__

#include <beep/percpu.h>
#include <beep/threads.h>

typedef struct {
	/* Dcache line 1 */
	unsigned int	__softirq_pending; /* must be 1st, see rtrap.S */
	unsigned int	__nmi_count;
	unsigned long	clock_tick;	/* %tick's per second */
	unsigned long	__pad;
	unsigned int	irq0_irqs;
	unsigned int	__pad2;

	/* Dcache line 2, rarely used */
	unsigned int	dcache_size;
	unsigned int	dcache_line_size;
	unsigned int	icache_size;
	unsigned int	icache_line_size;
	unsigned int	ecache_size;
	unsigned int	ecache_line_size;
	int		core_id;
	int		proc_id;
} cpuinfo_sparc;

DECLARE_PER_CPU(cpuinfo_sparc, __cpu_data);
#define cpu_data(__cpu)		per_cpu(__cpu_data, (__cpu))
#define local_cpu_data()	__get_cpu_var(__cpu_data)

extern const struct seq_operations cpuinfo_op;

#endif /* !(__ASSEMBLY__) */

#include <asm/trap_block.h>

#endif /* _SPARC64_CPUDATA_H */
