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
#include <beep/errno.h>
#include <asm/sram.h>

/*
 * This provides a standard SRAM pool for tiny memories that can be
 * added either by the CPU or the platform code. Typical SRAM sizes
 * to be inserted in to the pool will generally be less than the page
 * size, with anything more reasonably sized handled as a NUMA memory
 * node.
 */
struct gen_pool *sram_pool;

static int __init sram_pool_init(void)
{
	/*
	 * This is a global pool, we don't care about node locality.
	 */
	sram_pool = gen_pool_create(1, -1);
	if (unlikely(!sram_pool))
		return -ENOMEM;

	return 0;
}
core_initcall(sram_pool_init);
