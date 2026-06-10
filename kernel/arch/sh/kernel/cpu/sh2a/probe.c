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
	boot_cpu_data.family			= CPU_FAMILY_SH2A;

	/* All SH-2A CPUs have support for 16 and 32-bit opcodes.. */
	boot_cpu_data.flags			|= CPU_HAS_OP32;

#if defined(CONFIG_CPU_SUBTYPE_SH7201)
	boot_cpu_data.type			= CPU_SH7201;
	boot_cpu_data.flags			|= CPU_HAS_FPU;
#elif defined(CONFIG_CPU_SUBTYPE_SH7203)
	boot_cpu_data.type			= CPU_SH7203;
	boot_cpu_data.flags			|= CPU_HAS_FPU;
#elif defined(CONFIG_CPU_SUBTYPE_SH7263)
	boot_cpu_data.type			= CPU_SH7263;
	boot_cpu_data.flags			|= CPU_HAS_FPU;
#elif defined(CONFIG_CPU_SUBTYPE_SH7264)
	boot_cpu_data.type			= CPU_SH7264;
	boot_cpu_data.flags			|= CPU_HAS_FPU;
#elif defined(CONFIG_CPU_SUBTYPE_SH7269)
	boot_cpu_data.type			= CPU_SH7269;
	boot_cpu_data.flags			|= CPU_HAS_FPU;
#elif defined(CONFIG_CPU_SUBTYPE_SH7206)
	boot_cpu_data.type			= CPU_SH7206;
	boot_cpu_data.flags			|= CPU_HAS_DSP;
#elif defined(CONFIG_CPU_SUBTYPE_MXG)
	boot_cpu_data.type			= CPU_MXG;
	boot_cpu_data.flags			|= CPU_HAS_DSP;
#endif

	boot_cpu_data.dcache.ways		= 4;
	boot_cpu_data.dcache.way_incr		= (1 << 11);
	boot_cpu_data.dcache.sets		= 128;
	boot_cpu_data.dcache.entry_shift	= 4;
	boot_cpu_data.dcache.linesz		= L1_CACHE_BYTES;
	boot_cpu_data.dcache.flags		= 0;

	/*
	 * The icache is the same as the dcache as far as this setup is
	 * concerned. The only real difference in hardware is that the icache
	 * lacks the U bit that the dcache has, none of this has any bearing
	 * on the cache info.
	 */
	boot_cpu_data.icache		= boot_cpu_data.dcache;
}
