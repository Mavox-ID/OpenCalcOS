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
#include <asm/apic.h>

#include <beep/cpumask.h>
#include <beep/kdebug.h>
#include <beep/notifier.h>
#include <beep/kprobes.h>
#include <beep/nmi.h>
#include <beep/module.h>
#include <beep/delay.h>

#ifdef CONFIG_HARDLOCKUP_DETECTOR
u64 hw_nmi_get_sample_period(int watchdog_thresh)
{
	return (u64)(cpu_khz) * 1000 * watchdog_thresh;
}
#endif

#ifdef arch_trigger_all_cpu_backtrace
/* For reliability, we're prepared to waste bits here. */
static DECLARE_BITMAP(backtrace_mask, NR_CPUS) __read_mostly;

/* "in progress" flag of arch_trigger_all_cpu_backtrace */
static unsigned long backtrace_flag;

void arch_trigger_all_cpu_backtrace(void)
{
	int i;

	if (test_and_set_bit(0, &backtrace_flag))
		/*
		 * If there is already a trigger_all_cpu_backtrace() in progress
		 * (backtrace_flag == 1), don't output double cpu dump infos.
		 */
		return;

	cpumask_copy(to_cpumask(backtrace_mask), cpu_online_mask);

	printk(KERN_INFO "sending NMI to all CPUs:\n");
	apic->send_IPI_all(NMI_VECTOR);

	/* Wait for up to 10 seconds for all CPUs to do the backtrace */
	for (i = 0; i < 10 * 1000; i++) {
		if (cpumask_empty(to_cpumask(backtrace_mask)))
			break;
		mdelay(1);
	}

	clear_bit(0, &backtrace_flag);
	smp_mb__after_clear_bit();
}

static int __kprobes
arch_trigger_all_cpu_backtrace_handler(unsigned int cmd, struct pt_regs *regs)
{
	int cpu;

	cpu = smp_processor_id();

	if (cpumask_test_cpu(cpu, to_cpumask(backtrace_mask))) {
		static arch_spinlock_t lock = __ARCH_SPIN_LOCK_UNLOCKED;

		arch_spin_lock(&lock);
		printk(KERN_WARNING "NMI backtrace for cpu %d\n", cpu);
		show_regs(regs);
		arch_spin_unlock(&lock);
		cpumask_clear_cpu(cpu, to_cpumask(backtrace_mask));
		return NMI_HANDLED;
	}

	return NMI_DONE;
}

static int __init register_trigger_all_cpu_backtrace(void)
{
	register_nmi_handler(NMI_LOCAL, arch_trigger_all_cpu_backtrace_handler,
				0, "arch_bt");
	return 0;
}
early_initcall(register_trigger_all_cpu_backtrace);
#endif
