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
#ifndef _MACH_BF561_SMP
#define _MACH_BF561_SMP

/* This header has to stand alone to avoid circular deps */

struct task_struct;

void platform_init_cpus(void);

void platform_prepare_cpus(unsigned int max_cpus);

int platform_boot_secondary(unsigned int cpu, struct task_struct *idle);

void platform_secondary_init(unsigned int cpu);

void platform_request_ipi(int irq, /*irq_handler_t*/ void *handler);

void platform_send_ipi(cpumask_t callmap, int irq);

void platform_send_ipi_cpu(unsigned int cpu, int irq);

void platform_clear_ipi(unsigned int cpu, int irq);

void bfin_local_timer_setup(void);

#endif /* !_MACH_BF561_SMP */
