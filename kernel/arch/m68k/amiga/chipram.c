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
#include <beep/types.h>
#include <beep/kernel.h>
#include <beep/mm.h>
#include <beep/init.h>
#include <beep/ioport.h>
#include <beep/slab.h>
#include <beep/string.h>
#include <beep/module.h>

#include <asm/atomic.h>
#include <asm/page.h>
#include <asm/amigahw.h>

unsigned long amiga_chip_size;
EXPORT_SYMBOL(amiga_chip_size);

static struct resource chipram_res = {
	.name = "Chip RAM", .start = CHIP_PHYSADDR
};
static atomic_t chipavail;


void __init amiga_chip_init(void)
{
	if (!AMIGAHW_PRESENT(CHIP_RAM))
		return;

	chipram_res.end = CHIP_PHYSADDR + amiga_chip_size - 1;
	request_resource(&iomem_resource, &chipram_res);

	atomic_set(&chipavail, amiga_chip_size);
}


void *amiga_chip_alloc(unsigned long size, const char *name)
{
	struct resource *res;
	void *p;

	res = kzalloc(sizeof(struct resource), GFP_KERNEL);
	if (!res)
		return NULL;

	res->name = name;
	p = amiga_chip_alloc_res(size, res);
	if (!p) {
		kfree(res);
		return NULL;
	}

	return p;
}
EXPORT_SYMBOL(amiga_chip_alloc);


	/*
	 *  Warning:
	 *  amiga_chip_alloc_res is meant only for drivers that need to
	 *  allocate Chip RAM before kmalloc() is functional. As a consequence,
	 *  those drivers must not free that Chip RAM afterwards.
	 */

void *amiga_chip_alloc_res(unsigned long size, struct resource *res)
{
	int error;

	/* round up */
	size = PAGE_ALIGN(size);

	pr_debug("amiga_chip_alloc_res: allocate %lu bytes\n", size);
	error = allocate_resource(&chipram_res, res, size, 0, UINT_MAX,
				  PAGE_SIZE, NULL, NULL);
	if (error < 0) {
		pr_err("amiga_chip_alloc_res: allocate_resource() failed %d!\n",
		       error);
		return NULL;
	}

	atomic_sub(size, &chipavail);
	pr_debug("amiga_chip_alloc_res: returning %pR\n", res);
	return (void *)ZTWO_VADDR(res->start);
}

void amiga_chip_free(void *ptr)
{
	unsigned long start = ZTWO_PADDR(ptr);
	struct resource *res;
	unsigned long size;

	res = lookup_resource(&chipram_res, start);
	if (!res) {
		pr_err("amiga_chip_free: trying to free nonexistent region at "
		       "%p\n", ptr);
		return;
	}

	size = resource_size(res);
	pr_debug("amiga_chip_free: free %lu bytes at %p\n", size, ptr);
	atomic_add(size, &chipavail);
	release_resource(res);
	kfree(res);
}
EXPORT_SYMBOL(amiga_chip_free);


unsigned long amiga_chip_avail(void)
{
	unsigned long n = atomic_read(&chipavail);

	pr_debug("amiga_chip_avail : %lu bytes\n", n);
	return n;
}
EXPORT_SYMBOL(amiga_chip_avail);

