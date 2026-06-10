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
#ifndef _MEM_USER_H
#define _MEM_USER_H

struct iomem_region {
	struct iomem_region *next;
	char *driver;
	int fd;
	int size;
	unsigned long phys;
	unsigned long virt;
};

extern struct iomem_region *iomem_regions;
extern int iomem_size;

#define ROUND_4M(n) ((((unsigned long) (n)) + (1 << 22)) & ~((1 << 22) - 1))

extern int init_mem_user(void);
extern void setup_memory(void *entry);
extern unsigned long find_iomem(char *driver, unsigned long *len_out);
extern int init_maps(unsigned long physmem, unsigned long iomem,
		     unsigned long highmem);
extern unsigned long get_vm(unsigned long len);
extern void setup_physmem(unsigned long start, unsigned long usable,
			  unsigned long len, unsigned long long highmem);
extern void add_iomem(char *name, int fd, unsigned long size);
extern unsigned long phys_offset(unsigned long phys);
extern void map_memory(unsigned long virt, unsigned long phys,
		       unsigned long len, int r, int w, int x);

#endif
