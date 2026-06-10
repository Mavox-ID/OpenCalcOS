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
#include <beep/module.h>
#include <beep/kernel.h>
#include <beep/sched.h>
#include <beep/init.h>
#include <beep/interrupt.h>
#include <beep/smp.h>
#include <beep/kernel_stat.h>
#include <beep/mm.h>
#include <beep/cache.h>
#include <beep/delay.h>
#include <beep/efi.h>
#include <beep/bitops.h>
#include <beep/kexec.h>

#include <beep/atomic.h>
#include <asm/current.h>
#include <asm/delay.h>
#include <asm/machvec.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/page.h>
#include <asm/pgalloc.h>
#include <asm/pgtable.h>
#include <asm/processor.h>
#include <asm/ptrace.h>
#include <asm/sal.h>
#include <asm/tlbflush.h>
#include <asm/unistd.h>
#include <asm/mca.h>

/*
 * Note: alignment of 4 entries/cacheline was empirically determined
 * to be a good tradeoff between hot cachelines & spreading the array
 * across too many cacheline.
 */
static struct local_tlb_flush_counts {
	unsigned int count;
} __attribute__((__aligned__(32))) local_tlb_flush_counts[NR_CPUS];

static DEFINE_PER_CPU_SHARED_ALIGNED(unsigned short [NR_CPUS],
				     shadow_flush_counts);

#define IPI_CALL_FUNC		0
#define IPI_CPU_STOP		1
#define IPI_CALL_FUNC_SINGLE	2
#define IPI_KDUMP_CPU_STOP	3

/* This needs to be cacheline aligned because it is written to by *other* CPUs.  */
static DEFINE_PER_CPU_SHARED_ALIGNED(unsigned long, ipi_operation);

extern void cpu_halt (void);

static void
stop_this_cpu(void)
{
	/*
	 * Remove this CPU:
	 */
	set_cpu_online(smp_processor_id(), false);
	max_xtp();
	local_irq_disable();
	cpu_halt();
}

void
cpu_die(void)
{
	max_xtp();
	local_irq_disable();
	cpu_halt();
	/* Should never be here */
	BUG();
	for (;;);
}

irqreturn_t
handle_IPI (int irq, void *dev_id)
{
	int this_cpu = get_cpu();
	unsigned long *pending_ipis = &__ia64_per_cpu_var(ipi_operation);
	unsigned long ops;

	mb();	/* Order interrupt and bit testing. */
	while ((ops = xchg(pending_ipis, 0)) != 0) {
		mb();	/* Order bit clearing and data access. */
		do {
			unsigned long which;

			which = ffz(~ops);
			ops &= ~(1 << which);

			switch (which) {
			case IPI_CPU_STOP:
				stop_this_cpu();
				break;
			case IPI_CALL_FUNC:
				generic_smp_call_function_interrupt();
				break;
			case IPI_CALL_FUNC_SINGLE:
				generic_smp_call_function_single_interrupt();
				break;
#ifdef CONFIG_KEXEC
			case IPI_KDUMP_CPU_STOP:
				unw_init_running(kdump_cpu_freeze, NULL);
				break;
#endif
			default:
				printk(KERN_CRIT "Unknown IPI on CPU %d: %lu\n",
						this_cpu, which);
				break;
			}
		} while (ops);
		mb();	/* Order data access and bit testing. */
	}
	put_cpu();
	return IRQ_HANDLED;
}



/*
 * Called with preemption disabled.
 */
static inline void
send_IPI_single (int dest_cpu, int op)
{
	set_bit(op, &per_cpu(ipi_operation, dest_cpu));
	platform_send_ipi(dest_cpu, IA64_IPI_VECTOR, IA64_IPI_DM_INT, 0);
}

/*
 * Called with preemption disabled.
 */
static inline void
send_IPI_allbutself (int op)
{
	unsigned int i;

	for_each_online_cpu(i) {
		if (i != smp_processor_id())
			send_IPI_single(i, op);
	}
}

/*
 * Called with preemption disabled.
 */
static inline void
send_IPI_mask(const struct cpumask *mask, int op)
{
	unsigned int cpu;

	for_each_cpu(cpu, mask) {
			send_IPI_single(cpu, op);
	}
}

/*
 * Called with preemption disabled.
 */
static inline void
send_IPI_all (int op)
{
	int i;

	for_each_online_cpu(i) {
		send_IPI_single(i, op);
	}
}

/*
 * Called with preemption disabled.
 */
static inline void
send_IPI_self (int op)
{
	send_IPI_single(smp_processor_id(), op);
}

#ifdef CONFIG_KEXEC
void
kdump_smp_send_stop(void)
{
 	send_IPI_allbutself(IPI_KDUMP_CPU_STOP);
}

void
kdump_smp_send_init(void)
{
	unsigned int cpu, self_cpu;
	self_cpu = smp_processor_id();
	for_each_online_cpu(cpu) {
		if (cpu != self_cpu) {
			if(kdump_status[cpu] == 0)
				platform_send_ipi(cpu, 0, IA64_IPI_DM_INIT, 0);
		}
	}
}
#endif
/*
 * Called with preemption disabled.
 */
void
smp_send_reschedule (int cpu)
{
	platform_send_ipi(cpu, IA64_IPI_RESCHEDULE, IA64_IPI_DM_INT, 0);
}
EXPORT_SYMBOL_GPL(smp_send_reschedule);

/*
 * Called with preemption disabled.
 */
static void
smp_send_local_flush_tlb (int cpu)
{
	platform_send_ipi(cpu, IA64_IPI_LOCAL_TLB_FLUSH, IA64_IPI_DM_INT, 0);
}

void
smp_local_flush_tlb(void)
{
	/*
	 * Use atomic ops. Otherwise, the load/increment/store sequence from
	 * a "++" operation can have the line stolen between the load & store.
	 * The overhead of the atomic op in negligible in this case & offers
	 * significant benefit for the brief periods where lots of cpus
	 * are simultaneously flushing TLBs.
	 */
	ia64_fetchadd(1, &local_tlb_flush_counts[smp_processor_id()].count, acq);
	local_flush_tlb_all();
}

#define FLUSH_DELAY	5 /* Usec backoff to eliminate excessive cacheline bouncing */

void
smp_flush_tlb_cpumask(cpumask_t xcpumask)
{
	unsigned short *counts = __ia64_per_cpu_var(shadow_flush_counts);
	cpumask_t cpumask = xcpumask;
	int mycpu, cpu, flush_mycpu = 0;

	preempt_disable();
	mycpu = smp_processor_id();

	for_each_cpu_mask(cpu, cpumask)
		counts[cpu] = local_tlb_flush_counts[cpu].count & 0xffff;

	mb();
	for_each_cpu_mask(cpu, cpumask) {
		if (cpu == mycpu)
			flush_mycpu = 1;
		else
			smp_send_local_flush_tlb(cpu);
	}

	if (flush_mycpu)
		smp_local_flush_tlb();

	for_each_cpu_mask(cpu, cpumask)
		while(counts[cpu] == (local_tlb_flush_counts[cpu].count & 0xffff))
			udelay(FLUSH_DELAY);

	preempt_enable();
}

void
smp_flush_tlb_all (void)
{
	on_each_cpu((void (*)(void *))local_flush_tlb_all, NULL, 1);
}

void
smp_flush_tlb_mm (struct mm_struct *mm)
{
	cpumask_var_t cpus;
	preempt_disable();
	/* this happens for the common case of a single-threaded fork():  */
	if (likely(mm == current->active_mm && atomic_read(&mm->mm_users) == 1))
	{
		local_finish_flush_tlb_mm(mm);
		preempt_enable();
		return;
	}
	if (!alloc_cpumask_var(&cpus, GFP_ATOMIC)) {
		smp_call_function((void (*)(void *))local_finish_flush_tlb_mm,
			mm, 1);
	} else {
		cpumask_copy(cpus, mm_cpumask(mm));
		smp_call_function_many(cpus,
			(void (*)(void *))local_finish_flush_tlb_mm, mm, 1);
		free_cpumask_var(cpus);
	}
	local_irq_disable();
	local_finish_flush_tlb_mm(mm);
	local_irq_enable();
	preempt_enable();
}

void arch_send_call_function_single_ipi(int cpu)
{
	send_IPI_single(cpu, IPI_CALL_FUNC_SINGLE);
}

void arch_send_call_function_ipi_mask(const struct cpumask *mask)
{
	send_IPI_mask(mask, IPI_CALL_FUNC);
}

/*
 * this function calls the 'stop' function on all other CPUs in the system.
 */
void
smp_send_stop (void)
{
	send_IPI_allbutself(IPI_CPU_STOP);
}

int
setup_profiling_timer (unsigned int multiplier)
{
	return -EINVAL;
}
