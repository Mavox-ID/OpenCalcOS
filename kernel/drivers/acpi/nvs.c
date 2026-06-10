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
#include <beep/io.h>
#include <beep/kernel.h>
#include <beep/list.h>
#include <beep/mm.h>
#include <beep/slab.h>
#include <beep/acpi.h>
#include <beep/acpi_io.h>
#include <acpi/acpiosxf.h>

/* ACPI NVS regions, APEI may use it */

struct nvs_region {
	__u64 phys_start;
	__u64 size;
	struct list_head node;
};

static LIST_HEAD(nvs_region_list);

#ifdef CONFIG_ACPI_SLEEP
static int suspend_nvs_register(unsigned long start, unsigned long size);
#else
static inline int suspend_nvs_register(unsigned long a, unsigned long b)
{
	return 0;
}
#endif

int acpi_nvs_register(__u64 start, __u64 size)
{
	struct nvs_region *region;

	region = kmalloc(sizeof(*region), GFP_KERNEL);
	if (!region)
		return -ENOMEM;
	region->phys_start = start;
	region->size = size;
	list_add_tail(&region->node, &nvs_region_list);

	return suspend_nvs_register(start, size);
}

int acpi_nvs_for_each_region(int (*func)(__u64 start, __u64 size, void *data),
			     void *data)
{
	int rc;
	struct nvs_region *region;

	list_for_each_entry(region, &nvs_region_list, node) {
		rc = func(region->phys_start, region->size, data);
		if (rc)
			return rc;
	}

	return 0;
}


#ifdef CONFIG_ACPI_SLEEP
/*
 * Platforms, like ACPI, may want us to save some memory used by them during
 * suspend and to restore the contents of this memory during the subsequent
 * resume.  The code below implements a mechanism allowing us to do that.
 */

struct nvs_page {
	unsigned long phys_start;
	unsigned int size;
	void *kaddr;
	void *data;
	bool unmap;
	struct list_head node;
};

static LIST_HEAD(nvs_list);

/**
 *	suspend_nvs_register - register platform NVS memory region to save
 *	@start - physical address of the region
 *	@size - size of the region
 *
 *	The NVS region need not be page-aligned (both ends) and we arrange
 *	things so that the data from page-aligned addresses in this region will
 *	be copied into separate RAM pages.
 */
static int suspend_nvs_register(unsigned long start, unsigned long size)
{
	struct nvs_page *entry, *next;

	pr_info("PM: Registering ACPI NVS region [mem %#010lx-%#010lx] (%ld bytes)\n",
		start, start + size - 1, size);

	while (size > 0) {
		unsigned int nr_bytes;

		entry = kzalloc(sizeof(struct nvs_page), GFP_KERNEL);
		if (!entry)
			goto Error;

		list_add_tail(&entry->node, &nvs_list);
		entry->phys_start = start;
		nr_bytes = PAGE_SIZE - (start & ~PAGE_MASK);
		entry->size = (size < nr_bytes) ? size : nr_bytes;

		start += entry->size;
		size -= entry->size;
	}
	return 0;

 Error:
	list_for_each_entry_safe(entry, next, &nvs_list, node) {
		list_del(&entry->node);
		kfree(entry);
	}
	return -ENOMEM;
}

/**
 *	suspend_nvs_free - free data pages allocated for saving NVS regions
 */
void suspend_nvs_free(void)
{
	struct nvs_page *entry;

	list_for_each_entry(entry, &nvs_list, node)
		if (entry->data) {
			free_page((unsigned long)entry->data);
			entry->data = NULL;
			if (entry->kaddr) {
				if (entry->unmap) {
					iounmap(entry->kaddr);
					entry->unmap = false;
				} else {
					acpi_os_unmap_memory(entry->kaddr,
							     entry->size);
				}
				entry->kaddr = NULL;
			}
		}
}

/**
 *	suspend_nvs_alloc - allocate memory necessary for saving NVS regions
 */
int suspend_nvs_alloc(void)
{
	struct nvs_page *entry;

	list_for_each_entry(entry, &nvs_list, node) {
		entry->data = (void *)__get_free_page(GFP_KERNEL);
		if (!entry->data) {
			suspend_nvs_free();
			return -ENOMEM;
		}
	}
	return 0;
}

/**
 *	suspend_nvs_save - save NVS memory regions
 */
int suspend_nvs_save(void)
{
	struct nvs_page *entry;

	printk(KERN_INFO "PM: Saving platform NVS memory\n");

	list_for_each_entry(entry, &nvs_list, node)
		if (entry->data) {
			unsigned long phys = entry->phys_start;
			unsigned int size = entry->size;

			entry->kaddr = acpi_os_get_iomem(phys, size);
			if (!entry->kaddr) {
				entry->kaddr = acpi_os_ioremap(phys, size);
				entry->unmap = !!entry->kaddr;
			}
			if (!entry->kaddr) {
				suspend_nvs_free();
				return -ENOMEM;
			}
			memcpy(entry->data, entry->kaddr, entry->size);
		}

	return 0;
}

/**
 *	suspend_nvs_restore - restore NVS memory regions
 *
 *	This function is going to be called with interrupts disabled, so it
 *	cannot iounmap the virtual addresses used to access the NVS region.
 */
void suspend_nvs_restore(void)
{
	struct nvs_page *entry;

	printk(KERN_INFO "PM: Restoring platform NVS memory\n");

	list_for_each_entry(entry, &nvs_list, node)
		if (entry->data)
			memcpy(entry->kaddr, entry->data, entry->size);
}
#endif
