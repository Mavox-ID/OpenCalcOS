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
#include <beep/smp.h>

#include <asm/cacheflush.h>
#include <asm/smp_plat.h>

#include "sleep.h"
#include "tegra_cpu_car.h"

static void (*tegra_hotplug_shutdown)(void);

/*
 * platform-specific code to shutdown a CPU
 *
 * Called with IRQs disabled
 */
void __ref tegra_cpu_die(unsigned int cpu)
{
	cpu = cpu_logical_map(cpu);

	/* Flush the L1 data cache. */
	flush_cache_all();

	/* Shut down the current CPU. */
	tegra_hotplug_shutdown();

	/* Clock gate the CPU */
	tegra_wait_cpu_in_reset(cpu);
	tegra_disable_cpu_clock(cpu);

	/* Should never return here. */
	BUG();
}

int tegra_cpu_disable(unsigned int cpu)
{
	/*
	 * we don't allow CPU 0 to be shutdown (it is still too special
	 * e.g. clock tick interrupts)
	 */
	return cpu == 0 ? -EPERM : 0;
}

#ifdef CONFIG_ARCH_TEGRA_2x_SOC
extern void tegra20_hotplug_shutdown(void);
void __init tegra20_hotplug_init(void)
{
	tegra_hotplug_shutdown = tegra20_hotplug_shutdown;
}
#endif

#ifdef CONFIG_ARCH_TEGRA_3x_SOC
extern void tegra30_hotplug_shutdown(void);
void __init tegra30_hotplug_init(void)
{
	tegra_hotplug_shutdown = tegra30_hotplug_shutdown;
}
#endif
