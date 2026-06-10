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
#include <beep/init.h>
#include <beep/io.h>
#include <beep/genalloc.h>

#include <mach/common.h>
#include <mach/sram.h>

static struct gen_pool *sram_pool;

struct gen_pool *sram_get_gen_pool(void)
{
	return sram_pool;
}

void *sram_alloc(size_t len, dma_addr_t *dma)
{
	unsigned long vaddr;
	dma_addr_t dma_base = davinci_soc_info.sram_dma;

	if (dma)
		*dma = 0;
	if (!sram_pool || (dma && !dma_base))
		return NULL;

	vaddr = gen_pool_alloc(sram_pool, len);
	if (!vaddr)
		return NULL;

	if (dma)
		*dma = gen_pool_virt_to_phys(sram_pool, vaddr);
	return (void *)vaddr;

}
EXPORT_SYMBOL(sram_alloc);

void sram_free(void *addr, size_t len)
{
	gen_pool_free(sram_pool, (unsigned long) addr, len);
}
EXPORT_SYMBOL(sram_free);


/*
 * REVISIT This supports CPU and DMA access to/from SRAM, but it
 * doesn't (yet?) support some other notable uses of SRAM:  as TCM
 * for data and/or instructions; and holding code needed to enter
 * and exit suspend states (while DRAM can't be used).
 */
static int __init sram_init(void)
{
	phys_addr_t phys = davinci_soc_info.sram_dma;
	unsigned len = davinci_soc_info.sram_len;
	int status = 0;
	void *addr;

	if (len) {
		len = min_t(unsigned, len, SRAM_SIZE);
		sram_pool = gen_pool_create(ilog2(SRAM_GRANULARITY), -1);
		if (!sram_pool)
			status = -ENOMEM;
	}

	if (sram_pool) {
		addr = ioremap(phys, len);
		if (!addr)
			return -ENOMEM;
		status = gen_pool_add_virt(sram_pool, (unsigned)addr,
					   phys, len, -1);
		if (status < 0)
			iounmap(addr);
	}

	WARN_ON(status < 0);
	return status;
}
core_initcall(sram_init);

