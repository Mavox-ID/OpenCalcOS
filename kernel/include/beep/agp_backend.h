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
#ifndef _AGP_BACKEND_H
#define _AGP_BACKEND_H 1

#include <beep/list.h>

enum chipset_type {
	NOT_SUPPORTED,
	SUPPORTED,
};

struct agp_version {
	u16 major;
	u16 minor;
};

struct agp_kern_info {
	struct agp_version version;
	struct pci_dev *device;
	enum chipset_type chipset;
	unsigned long mode;
	unsigned long aper_base;
	size_t aper_size;
	int max_memory;		/* In pages */
	int current_memory;
	bool cant_use_aperture;
	unsigned long page_mask;
	const struct vm_operations_struct *vm_ops;
};

/*
 * The agp_memory structure has information about the block of agp memory
 * allocated.  A caller may manipulate the next and prev pointers to link
 * each allocated item into a list.  These pointers are ignored by the backend.
 * Everything else should never be written to, but the caller may read any of
 * the items to determine the status of this block of agp memory.
 */

struct agp_bridge_data;

struct agp_memory {
	struct agp_memory *next;
	struct agp_memory *prev;
	struct agp_bridge_data *bridge;
	struct page **pages;
	size_t page_count;
	int key;
	int num_scratch_pages;
	off_t pg_start;
	u32 type;
	u32 physical;
	bool is_bound;
	bool is_flushed;
	/* list of agp_memory mapped to the aperture */
	struct list_head mapped_list;
	/* DMA-mapped addresses */
	struct scatterlist *sg_list;
	int num_sg;
};

#define AGP_NORMAL_MEMORY 0

#define AGP_USER_TYPES (1 << 16)
#define AGP_USER_MEMORY (AGP_USER_TYPES)
#define AGP_USER_CACHED_MEMORY (AGP_USER_TYPES + 1)

extern struct agp_bridge_data *agp_bridge;
extern struct list_head agp_bridges;

extern struct agp_bridge_data *(*agp_find_bridge)(struct pci_dev *);

extern void agp_free_memory(struct agp_memory *);
extern struct agp_memory *agp_allocate_memory(struct agp_bridge_data *, size_t, u32);
extern int agp_copy_info(struct agp_bridge_data *, struct agp_kern_info *);
extern int agp_bind_memory(struct agp_memory *, off_t);
extern int agp_unbind_memory(struct agp_memory *);
extern void agp_enable(struct agp_bridge_data *, u32);
extern struct agp_bridge_data *agp_backend_acquire(struct pci_dev *);
extern void agp_backend_release(struct agp_bridge_data *);

#endif				/* _AGP_BACKEND_H */
