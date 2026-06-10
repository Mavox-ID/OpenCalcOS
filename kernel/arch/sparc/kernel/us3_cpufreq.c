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
#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/sched.h>
#include <beep/smp.h>
#include <beep/cpufreq.h>
#include <beep/threads.h>
#include <beep/slab.h>
#include <beep/init.h>

#include <asm/head.h>
#include <asm/timer.h>

static struct cpufreq_driver *cpufreq_us3_driver;

struct us3_freq_percpu_info {
	struct cpufreq_frequency_table table[4];
};

/* Indexed by cpu number. */
static struct us3_freq_percpu_info *us3_freq_table;

/* UltraSPARC-III has three dividers: 1, 2, and 32.  These are controlled
 * in the Safari config register.
 */
#define SAFARI_CFG_DIV_1	0x0000000000000000UL
#define SAFARI_CFG_DIV_2	0x0000000040000000UL
#define SAFARI_CFG_DIV_32	0x0000000080000000UL
#define SAFARI_CFG_DIV_MASK	0x00000000C0000000UL

static unsigned long read_safari_cfg(void)
{
	unsigned long ret;

	__asm__ __volatile__("ldxa	[%%g0] %1, %0"
			     : "=&r" (ret)
			     : "i" (ASI_SAFARI_CONFIG));
	return ret;
}

static void write_safari_cfg(unsigned long val)
{
	__asm__ __volatile__("stxa	%0, [%%g0] %1\n\t"
			     "membar	#Sync"
			     : /* no outputs */
			     : "r" (val), "i" (ASI_SAFARI_CONFIG)
			     : "memory");
}

static unsigned long get_current_freq(unsigned int cpu, unsigned long safari_cfg)
{
	unsigned long clock_tick = sparc64_get_clock_tick(cpu) / 1000;
	unsigned long ret;

	switch (safari_cfg & SAFARI_CFG_DIV_MASK) {
	case SAFARI_CFG_DIV_1:
		ret = clock_tick / 1;
		break;
	case SAFARI_CFG_DIV_2:
		ret = clock_tick / 2;
		break;
	case SAFARI_CFG_DIV_32:
		ret = clock_tick / 32;
		break;
	default:
		BUG();
	}

	return ret;
}

static unsigned int us3_freq_get(unsigned int cpu)
{
	cpumask_t cpus_allowed;
	unsigned long reg;
	unsigned int ret;

	if (!cpu_online(cpu))
		return 0;

	cpumask_copy(&cpus_allowed, tsk_cpus_allowed(current));
	set_cpus_allowed_ptr(current, cpumask_of(cpu));

	reg = read_safari_cfg();
	ret = get_current_freq(cpu, reg);

	set_cpus_allowed_ptr(current, &cpus_allowed);

	return ret;
}

static void us3_set_cpu_divider_index(unsigned int cpu, unsigned int index)
{
	unsigned long new_bits, new_freq, reg;
	cpumask_t cpus_allowed;
	struct cpufreq_freqs freqs;

	if (!cpu_online(cpu))
		return;

	cpumask_copy(&cpus_allowed, tsk_cpus_allowed(current));
	set_cpus_allowed_ptr(current, cpumask_of(cpu));

	new_freq = sparc64_get_clock_tick(cpu) / 1000;
	switch (index) {
	case 0:
		new_bits = SAFARI_CFG_DIV_1;
		new_freq /= 1;
		break;
	case 1:
		new_bits = SAFARI_CFG_DIV_2;
		new_freq /= 2;
		break;
	case 2:
		new_bits = SAFARI_CFG_DIV_32;
		new_freq /= 32;
		break;

	default:
		BUG();
	}

	reg = read_safari_cfg();

	freqs.old = get_current_freq(cpu, reg);
	freqs.new = new_freq;
	freqs.cpu = cpu;
	cpufreq_notify_transition(&freqs, CPUFREQ_PRECHANGE);

	reg &= ~SAFARI_CFG_DIV_MASK;
	reg |= new_bits;
	write_safari_cfg(reg);

	cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);

	set_cpus_allowed_ptr(current, &cpus_allowed);
}

static int us3_freq_target(struct cpufreq_policy *policy,
			  unsigned int target_freq,
			  unsigned int relation)
{
	unsigned int new_index = 0;

	if (cpufreq_frequency_table_target(policy,
					   &us3_freq_table[policy->cpu].table[0],
					   target_freq,
					   relation,
					   &new_index))
		return -EINVAL;

	us3_set_cpu_divider_index(policy->cpu, new_index);

	return 0;
}

static int us3_freq_verify(struct cpufreq_policy *policy)
{
	return cpufreq_frequency_table_verify(policy,
					      &us3_freq_table[policy->cpu].table[0]);
}

static int __init us3_freq_cpu_init(struct cpufreq_policy *policy)
{
	unsigned int cpu = policy->cpu;
	unsigned long clock_tick = sparc64_get_clock_tick(cpu) / 1000;
	struct cpufreq_frequency_table *table =
		&us3_freq_table[cpu].table[0];

	table[0].index = 0;
	table[0].frequency = clock_tick / 1;
	table[1].index = 1;
	table[1].frequency = clock_tick / 2;
	table[2].index = 2;
	table[2].frequency = clock_tick / 32;
	table[3].index = 0;
	table[3].frequency = CPUFREQ_TABLE_END;

	policy->cpuinfo.transition_latency = 0;
	policy->cur = clock_tick;

	return cpufreq_frequency_table_cpuinfo(policy, table);
}

static int us3_freq_cpu_exit(struct cpufreq_policy *policy)
{
	if (cpufreq_us3_driver)
		us3_set_cpu_divider_index(policy->cpu, 0);

	return 0;
}

static int __init us3_freq_init(void)
{
	unsigned long manuf, impl, ver;
	int ret;

	if (tlb_type != cheetah && tlb_type != cheetah_plus)
		return -ENODEV;

	__asm__("rdpr %%ver, %0" : "=r" (ver));
	manuf = ((ver >> 48) & 0xffff);
	impl  = ((ver >> 32) & 0xffff);

	if (manuf == CHEETAH_MANUF &&
	    (impl == CHEETAH_IMPL ||
	     impl == CHEETAH_PLUS_IMPL ||
	     impl == JAGUAR_IMPL ||
	     impl == PANTHER_IMPL)) {
		struct cpufreq_driver *driver;

		ret = -ENOMEM;
		driver = kzalloc(sizeof(struct cpufreq_driver), GFP_KERNEL);
		if (!driver)
			goto err_out;

		us3_freq_table = kzalloc(
			(NR_CPUS * sizeof(struct us3_freq_percpu_info)),
			GFP_KERNEL);
		if (!us3_freq_table)
			goto err_out;

		driver->init = us3_freq_cpu_init;
		driver->verify = us3_freq_verify;
		driver->target = us3_freq_target;
		driver->get = us3_freq_get;
		driver->exit = us3_freq_cpu_exit;
		driver->owner = THIS_MODULE,
		strcpy(driver->name, "UltraSPARC-III");

		cpufreq_us3_driver = driver;
		ret = cpufreq_register_driver(driver);
		if (ret)
			goto err_out;

		return 0;

err_out:
		if (driver) {
			kfree(driver);
			cpufreq_us3_driver = NULL;
		}
		kfree(us3_freq_table);
		us3_freq_table = NULL;
		return ret;
	}

	return -ENODEV;
}

static void __exit us3_freq_exit(void)
{
	if (cpufreq_us3_driver) {
		cpufreq_unregister_driver(cpufreq_us3_driver);
		kfree(cpufreq_us3_driver);
		cpufreq_us3_driver = NULL;
		kfree(us3_freq_table);
		us3_freq_table = NULL;
	}
}

MODULE_AUTHOR("David S. Miller <davem@redhat.com>");
MODULE_DESCRIPTION("cpufreq driver for UltraSPARC-III");
MODULE_LICENSE("GPL");

module_init(us3_freq_init);
module_exit(us3_freq_exit);
