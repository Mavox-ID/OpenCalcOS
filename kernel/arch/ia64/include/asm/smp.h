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
#ifndef _ASM_IA64_SMP_H
#define _ASM_IA64_SMP_H

#include <beep/init.h>
#include <beep/threads.h>
#include <beep/kernel.h>
#include <beep/cpumask.h>
#include <beep/bitops.h>
#include <beep/irqreturn.h>

#include <asm/io.h>
#include <asm/param.h>
#include <asm/processor.h>
#include <asm/ptrace.h>

static inline unsigned int
ia64_get_lid (void)
{
	union {
		struct {
			unsigned long reserved : 16;
			unsigned long eid : 8;
			unsigned long id : 8;
			unsigned long ignored : 32;
		} f;
		unsigned long bits;
	} lid;

	lid.bits = ia64_getreg(_IA64_REG_CR_LID);
	return lid.f.id << 8 | lid.f.eid;
}

#define hard_smp_processor_id()		ia64_get_lid()

#ifdef CONFIG_SMP

#define XTP_OFFSET		0x1e0008

#define SMP_IRQ_REDIRECTION	(1 << 0)
#define SMP_IPI_REDIRECTION	(1 << 1)

#define raw_smp_processor_id() (current_thread_info()->cpu)

extern struct smp_boot_data {
	int cpu_count;
	int cpu_phys_id[NR_CPUS];
} smp_boot_data __initdata;

extern char no_int_routing;

extern cpumask_t cpu_core_map[NR_CPUS];
DECLARE_PER_CPU_SHARED_ALIGNED(cpumask_t, cpu_sibling_map);
extern int smp_num_siblings;
extern void __iomem *ipi_base_addr;
extern unsigned char smp_int_redirect;

extern volatile int ia64_cpu_to_sapicid[];
#define cpu_physical_id(i)	ia64_cpu_to_sapicid[i]

extern unsigned long ap_wakeup_vector;

/*
 * Function to map hard smp processor id to logical id.  Slow, so don't use this in
 * performance-critical code.
 */
static inline int
cpu_logical_id (int cpuid)
{
	int i;

	for (i = 0; i < NR_CPUS; ++i)
		if (cpu_physical_id(i) == cpuid)
			break;
	return i;
}

/*
 * XTP control functions:
 *	min_xtp   : route all interrupts to this CPU
 *	normal_xtp: nominal XTP value
 *	max_xtp   : never deliver interrupts to this CPU.
 */

static inline void
min_xtp (void)
{
	if (smp_int_redirect & SMP_IRQ_REDIRECTION)
		writeb(0x00, ipi_base_addr + XTP_OFFSET); /* XTP to min */
}

static inline void
normal_xtp (void)
{
	if (smp_int_redirect & SMP_IRQ_REDIRECTION)
		writeb(0x08, ipi_base_addr + XTP_OFFSET); /* XTP normal */
}

static inline void
max_xtp (void)
{
	if (smp_int_redirect & SMP_IRQ_REDIRECTION)
		writeb(0x0f, ipi_base_addr + XTP_OFFSET); /* Set XTP to max */
}

/* Upping and downing of CPUs */
extern int __cpu_disable (void);
extern void __cpu_die (unsigned int cpu);
extern void cpu_die (void) __attribute__ ((noreturn));
extern void __init smp_build_cpu_map(void);

extern void __init init_smp_config (void);
extern void smp_do_timer (struct pt_regs *regs);

extern irqreturn_t handle_IPI(int irq, void *dev_id);
extern void smp_send_reschedule (int cpu);
extern void identify_siblings (struct cpuinfo_ia64 *);
extern int is_multithreading_enabled(void);

extern void arch_send_call_function_single_ipi(int cpu);
extern void arch_send_call_function_ipi_mask(const struct cpumask *mask);

#else /* CONFIG_SMP */

#define cpu_logical_id(i)		0
#define cpu_physical_id(i)		ia64_get_lid()

#endif /* CONFIG_SMP */
#endif /* _ASM_IA64_SMP_H */
