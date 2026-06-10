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
#include <asm/processor.h>
#include <asm/cache.h>

void __cpuinit cpu_probe(void)
{
#if defined(CONFIG_CPU_SUBTYPE_SH7619)
	boot_cpu_data.type			= CPU_SH7619;
	boot_cpu_data.dcache.ways		= 4;
	boot_cpu_data.dcache.way_incr	= (1<<12);
	boot_cpu_data.dcache.sets		= 256;
	boot_cpu_data.dcache.entry_shift	= 4;
	boot_cpu_data.dcache.linesz		= L1_CACHE_BYTES;
	boot_cpu_data.dcache.flags		= 0;
#endif
	/*
	 * SH-2 doesn't have separate caches
	 */
	boot_cpu_data.dcache.flags |= SH_CACHE_COMBINED;
	boot_cpu_data.icache = boot_cpu_data.dcache;
	boot_cpu_data.family = CPU_FAMILY_SH2;
}
