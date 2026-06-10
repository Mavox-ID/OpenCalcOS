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
#include <beep/sched.h>

/*
 * Send inter-processor interrupt
 */
static void up_send_ipi_single(int cpu, unsigned int action)
{
	panic(KERN_ERR "%s called", __func__);
}

static inline void up_send_ipi_mask(const struct cpumask *mask,
				    unsigned int action)
{
	panic(KERN_ERR "%s called", __func__);
}

/*
 *  After we've done initial boot, this function is called to allow the
 *  board code to clean up state, if needed
 */
static void __cpuinit up_init_secondary(void)
{
}

static void __cpuinit up_smp_finish(void)
{
}

/* Hook for after all CPUs are online */
static void up_cpus_done(void)
{
}

/*
 * Firmware CPU startup hook
 */
static void __cpuinit up_boot_secondary(int cpu, struct task_struct *idle)
{
}

static void __init up_smp_setup(void)
{
}

static void __init up_prepare_cpus(unsigned int max_cpus)
{
}

#ifdef CONFIG_HOTPLUG_CPU
static int up_cpu_disable(void)
{
	return -ENOSYS;
}

static void up_cpu_die(unsigned int cpu)
{
	BUG();
}
#endif

struct plat_smp_ops up_smp_ops = {
	.send_ipi_single	= up_send_ipi_single,
	.send_ipi_mask		= up_send_ipi_mask,
	.init_secondary		= up_init_secondary,
	.smp_finish		= up_smp_finish,
	.cpus_done		= up_cpus_done,
	.boot_secondary		= up_boot_secondary,
	.smp_setup		= up_smp_setup,
	.prepare_cpus		= up_prepare_cpus,
#ifdef CONFIG_HOTPLUG_CPU
	.cpu_disable		= up_cpu_disable,
	.cpu_die		= up_cpu_die,
#endif
};
