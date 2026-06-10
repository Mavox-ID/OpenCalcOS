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
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/io.h>
#include <asm/cache.h>

#define CCR_CACHE_SNM	0x40000		/* Hardware-assisted synonym avoidance */
#define CCR_CACHE_IBE	0x1000000	/* ICBI broadcast */

void __init shx3_cache_init(void)
{
	unsigned int ccr;

	ccr = __raw_readl(CCR);

	/*
	 * If we've got cache aliases, resolve them in hardware.
	 */
	if (boot_cpu_data.dcache.n_aliases || boot_cpu_data.icache.n_aliases) {
		ccr |= CCR_CACHE_SNM;

		boot_cpu_data.icache.n_aliases = 0;
		boot_cpu_data.dcache.n_aliases = 0;

		pr_info("Enabling hardware synonym avoidance\n");
	}

#ifdef CONFIG_SMP
	/*
	 * Broadcast I-cache block invalidations by default.
	 */
	ccr |= CCR_CACHE_IBE;
#endif

	writel_uncached(ccr, CCR);
}
