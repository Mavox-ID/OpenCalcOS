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
#include <beep/io.h>

#include <asm/cacheflush.h>
#include "omap-wakeupgen.h"

#include "common.h"

#include "powerdomain.h"

/*
 * platform-specific code to shutdown a CPU
 * Called with IRQs disabled
 */
void __ref omap4_cpu_die(unsigned int cpu)
{
	unsigned int boot_cpu = 0;
	void __iomem *base = omap_get_wakeupgen_base();

	flush_cache_all();
	dsb();

	/*
	 * we're ready for shutdown now, so do it
	 */
	if (omap_secure_apis_support()) {
		if (omap_modify_auxcoreboot0(0x0, 0x200) != 0x0)
			pr_err("Secure clear status failed\n");
	} else {
		__raw_writel(0, base + OMAP_AUX_CORE_BOOT_0);
	}


	for (;;) {
		/*
		 * Enter into low power state
		 */
		omap4_hotplug_cpu(cpu, PWRDM_POWER_OFF);

		if (omap_secure_apis_support())
			boot_cpu = omap_read_auxcoreboot0();
		else
			boot_cpu =
				__raw_readl(base + OMAP_AUX_CORE_BOOT_0) >> 5;

		if (boot_cpu == smp_processor_id()) {
			/*
			 * OK, proper wakeup, we're done
			 */
			break;
		}
		pr_debug("CPU%u: spurious wakeup call\n", cpu);
	}
}
