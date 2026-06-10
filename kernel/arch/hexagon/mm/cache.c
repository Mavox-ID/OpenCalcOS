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
#include <beep/mm.h>
#include <asm/cacheflush.h>
#include <asm/hexagon_vm.h>

#define spanlines(start, end) \
	(((end - (start & ~(LINESIZE - 1))) >> LINEBITS) + 1)

void flush_dcache_range(unsigned long start, unsigned long end)
{
	unsigned long lines = spanlines(start, end-1);
	unsigned long i, flags;

	start &= ~(LINESIZE - 1);

	local_irq_save(flags);

	for (i = 0; i < lines; i++) {
		__asm__ __volatile__ (
		"	dccleaninva(%0);	"
		:
		: "r" (start)
		);
		start += LINESIZE;
	}
	local_irq_restore(flags);
}

void flush_icache_range(unsigned long start, unsigned long end)
{
	unsigned long lines = spanlines(start, end-1);
	unsigned long i, flags;

	start &= ~(LINESIZE - 1);

	local_irq_save(flags);

	for (i = 0; i < lines; i++) {
		__asm__ __volatile__ (
			"	dccleana(%0); "
			"	icinva(%0);	"
			:
			: "r" (start)
		);
		start += LINESIZE;
	}
	__asm__ __volatile__ (
		"isync"
	);
	local_irq_restore(flags);
}

void hexagon_clean_dcache_range(unsigned long start, unsigned long end)
{
	unsigned long lines = spanlines(start, end-1);
	unsigned long i, flags;

	start &= ~(LINESIZE - 1);

	local_irq_save(flags);

	for (i = 0; i < lines; i++) {
		__asm__ __volatile__ (
		"	dccleana(%0);	"
		:
		: "r" (start)
		);
		start += LINESIZE;
	}
	local_irq_restore(flags);
}

void hexagon_inv_dcache_range(unsigned long start, unsigned long end)
{
	unsigned long lines = spanlines(start, end-1);
	unsigned long i, flags;

	start &= ~(LINESIZE - 1);

	local_irq_save(flags);

	for (i = 0; i < lines; i++) {
		__asm__ __volatile__ (
		"	dcinva(%0);	"
		:
		: "r" (start)
		);
		start += LINESIZE;
	}
	local_irq_restore(flags);
}




/*
 * This is just really brutal and shouldn't be used anyways,
 * especially on V2.  Left here just in case.
 */
void flush_cache_all_hexagon(void)
{
	unsigned long flags;
	local_irq_save(flags);
	__vmcache_ickill();
	__vmcache_dckill();
	__vmcache_l2kill();
	local_irq_restore(flags);
	mb();
}
