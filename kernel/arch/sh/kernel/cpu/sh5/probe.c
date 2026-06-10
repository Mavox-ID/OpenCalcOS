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
#include <beep/io.h>
#include <beep/string.h>
#include <asm/processor.h>
#include <asm/cache.h>
#include <asm/tlb.h>

void __cpuinit cpu_probe(void)
{
	unsigned long long cir;

	/*
	 * Do peeks in real mode to avoid having to set up a mapping for
	 * the WPC registers. On SH5-101 cut2, such a mapping would be
	 * exposed to an address translation erratum which would make it
	 * hard to set up correctly.
	 */
	cir = peek_real_address_q(0x0d000008);
	if ((cir & 0xffff) == 0x5103)
		boot_cpu_data.type = CPU_SH5_103;
	else if (((cir >> 32) & 0xffff) == 0x51e2)
		/* CPU.VCR aliased at CIR address on SH5-101 */
		boot_cpu_data.type = CPU_SH5_101;

	boot_cpu_data.family = CPU_FAMILY_SH5;

	/*
	 * First, setup some sane values for the I-cache.
	 */
	boot_cpu_data.icache.ways		= 4;
	boot_cpu_data.icache.sets		= 256;
	boot_cpu_data.icache.linesz		= L1_CACHE_BYTES;
	boot_cpu_data.icache.way_incr		= (1 << 13);
	boot_cpu_data.icache.entry_shift	= 5;
	boot_cpu_data.icache.way_size		= boot_cpu_data.icache.sets *
						  boot_cpu_data.icache.linesz;
	boot_cpu_data.icache.entry_mask		= 0x1fe0;
	boot_cpu_data.icache.flags		= 0;

	/*
	 * Next, setup some sane values for the D-cache.
	 *
	 * On the SH5, these are pretty consistent with the I-cache settings,
	 * so we just copy over the existing definitions.. these can be fixed
	 * up later, especially if we add runtime CPU probing.
	 *
	 * Though in the meantime it saves us from having to duplicate all of
	 * the above definitions..
	 */
	boot_cpu_data.dcache		= boot_cpu_data.icache;

	/*
	 * Setup any cache-related flags here
	 */
#if defined(CONFIG_CACHE_WRITETHROUGH)
	set_bit(SH_CACHE_MODE_WT, &(boot_cpu_data.dcache.flags));
#elif defined(CONFIG_CACHE_WRITEBACK)
	set_bit(SH_CACHE_MODE_WB, &(boot_cpu_data.dcache.flags));
#endif

	/* Setup some I/D TLB defaults */
	sh64_tlb_init();
}
