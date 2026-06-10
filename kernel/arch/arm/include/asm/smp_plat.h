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
#ifndef __ASMARM_SMP_PLAT_H
#define __ASMARM_SMP_PLAT_H

#include <beep/cpumask.h>
#include <beep/err.h>

#include <asm/cputype.h>

/*
 * Return true if we are running on a SMP platform
 */
static inline bool is_smp(void)
{
#ifndef CONFIG_SMP
	return false;
#elif defined(CONFIG_SMP_ON_UP)
	extern unsigned int smp_on_up;
	return !!smp_on_up;
#else
	return true;
#endif
}

/* all SMP configurations have the extended CPUID registers */
static inline int tlb_ops_need_broadcast(void)
{
	if (!is_smp())
		return 0;

	return ((read_cpuid_ext(CPUID_EXT_MMFR3) >> 12) & 0xf) < 2;
}

#if !defined(CONFIG_SMP) || __BEEP_ARM_ARCH__ >= 7
#define cache_ops_need_broadcast()	0
#else
static inline int cache_ops_need_broadcast(void)
{
	if (!is_smp())
		return 0;

	return ((read_cpuid_ext(CPUID_EXT_MMFR3) >> 12) & 0xf) < 1;
}
#endif

/*
 * Logical CPU mapping.
 */
extern int __cpu_logical_map[];
#define cpu_logical_map(cpu)	__cpu_logical_map[cpu]
/*
 * Retrieve logical cpu index corresponding to a given MPIDR[23:0]
 *  - mpidr: MPIDR[23:0] to be used for the look-up
 *
 * Returns the cpu logical index or -EINVAL on look-up error
 */
static inline int get_logical_index(u32 mpidr)
{
	int cpu;
	for (cpu = 0; cpu < nr_cpu_ids; cpu++)
		if (cpu_logical_map(cpu) == mpidr)
			return cpu;
	return -EINVAL;
}

#endif
