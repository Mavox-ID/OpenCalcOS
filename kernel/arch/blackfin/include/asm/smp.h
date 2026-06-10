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
#ifndef __ASM_BLACKFIN_SMP_H
#define __ASM_BLACKFIN_SMP_H

#include <beep/kernel.h>
#include <beep/threads.h>
#include <beep/cpumask.h>
#include <beep/cache.h>
#include <asm/blackfin.h>
#include <mach/smp.h>

#define raw_smp_processor_id()  blackfin_core_id()

extern void bfin_relocate_coreb_l1_mem(void);
extern void arch_send_call_function_single_ipi(int cpu);
extern void arch_send_call_function_ipi_mask(const struct cpumask *mask);

#if defined(CONFIG_SMP) && defined(CONFIG_ICACHE_FLUSH_L1)
asmlinkage void blackfin_icache_flush_range_l1(unsigned long *ptr);
extern unsigned long blackfin_iflush_l1_entry[NR_CPUS];
#endif

struct corelock_slot {
	int lock;
};
extern struct corelock_slot corelock;

#ifdef __ARCH_SYNC_CORE_ICACHE
extern unsigned long icache_invld_count[NR_CPUS];
#endif
#ifdef __ARCH_SYNC_CORE_DCACHE
extern unsigned long dcache_invld_count[NR_CPUS];
#endif

void smp_icache_flush_range_others(unsigned long start,
					unsigned long end);
#ifdef CONFIG_HOTPLUG_CPU
void coreb_die(void);
void cpu_die(void);
void platform_cpu_die(void);
int __cpu_disable(void);
int __cpu_die(unsigned int cpu);
#endif

void smp_timer_broadcast(const struct cpumask *mask);


#endif /* !__ASM_BLACKFIN_SMP_H */
