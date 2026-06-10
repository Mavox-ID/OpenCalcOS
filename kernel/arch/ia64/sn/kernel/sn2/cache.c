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
#include <beep/module.h>
#include <asm/pgalloc.h>
#include <asm/sn/arch.h>

/**
 * sn_flush_all_caches - flush a range of address from all caches (incl. L4)
 * @flush_addr: identity mapped region 7 address to start flushing
 * @bytes: number of bytes to flush
 *
 * Flush a range of addresses from all caches including L4. 
 * All addresses fully or partially contained within 
 * @flush_addr to @flush_addr + @bytes are flushed
 * from all caches.
 */
void
sn_flush_all_caches(long flush_addr, long bytes)
{
	unsigned long addr = flush_addr;

	/* SHub1 requires a cached address */
	if (is_shub1() && (addr & RGN_BITS) == RGN_BASE(RGN_UNCACHED))
		addr = (addr - RGN_BASE(RGN_UNCACHED)) + RGN_BASE(RGN_KERNEL);

	flush_icache_range(addr, addr + bytes);
	/*
	 * The last call may have returned before the caches
	 * were actually flushed, so we call it again to make
	 * sure.
	 */
	flush_icache_range(addr, addr + bytes);
	mb();
}
EXPORT_SYMBOL(sn_flush_all_caches);
