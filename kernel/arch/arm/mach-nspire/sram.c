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
#include <beep/io.h>
#include <beep/module.h>
#include <beep/spinlock.h>
#include <beep/genalloc.h>

static unsigned long sram_phys_base;
static __iomem void *sram_virt_base;
static struct gen_pool *sram_pool;

#define sram_phys_to_virt(p) (sram_virt_base + ((p) - sram_phys_base))

void *sram_alloc(unsigned int size, dma_addr_t *dma_addr)
{
	if (!sram_pool)
		return NULL;

	*dma_addr = gen_pool_alloc(sram_pool, size);
	pr_info("sram alloc - %dB@0x%p\n", size, (void *)*dma_addr);
	return sram_phys_to_virt(*dma_addr);
}
EXPORT_SYMBOL(sram_alloc);

void sram_free(dma_addr_t addr, unsigned int size)
{
	if (!sram_pool)
		return;

	gen_pool_free(sram_pool, addr, size);
}
EXPORT_SYMBOL(sram_free);

int __init sram_init(unsigned long base, unsigned long size)
{
	sram_phys_base = base;

	sram_pool = gen_pool_create(10, -1);
	if (!sram_pool) {
		pr_warn("Cannot create sram pool!\n");
		return -ENOMEM;
	}
	gen_pool_add(sram_pool, base, size, -1);
	sram_virt_base = ioremap(sram_phys_base, size);

	pr_info("sram pool: %ld KB@0x%p\n", size / 1024, sram_virt_base);
	return 0;
}
