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
#include <beep/errno.h>
#include <beep/smp.h>
#include <beep/cpumask.h>
#include <beep/delay.h>
#include <beep/of.h>
#include <mach/common.h>
#include <mach/r8a7779.h>
#include <mach/emev2.h>
#include <asm/cacheflush.h>
#include <asm/mach-types.h>

static cpumask_t dead_cpus;

void shmobile_cpu_die(unsigned int cpu)
{
	/* hardware shutdown code running on the CPU that is being offlined */
	flush_cache_all();
	dsb();

	/* notify platform_cpu_kill() that hardware shutdown is finished */
	cpumask_set_cpu(cpu, &dead_cpus);

	/* wait for SoC code in platform_cpu_kill() to shut off CPU core
	 * power. CPU bring up starts from the reset vector.
	 */
	while (1) {
		/*
		 * here's the WFI
		 */
		asm(".word	0xe320f003\n"
		    :
		    :
		    : "memory", "cc");
	}
}

int shmobile_cpu_disable(unsigned int cpu)
{
	cpumask_clear_cpu(cpu, &dead_cpus);
	/*
	 * we don't allow CPU 0 to be shutdown (it is still too special
	 * e.g. clock tick interrupts)
	 */
	return cpu == 0 ? -EPERM : 0;
}

int shmobile_cpu_is_dead(unsigned int cpu)
{
	return cpumask_test_cpu(cpu, &dead_cpus);
}
