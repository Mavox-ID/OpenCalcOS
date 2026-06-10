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
#ifndef __UNICORE_MEMBLOCK_H__
#define __UNICORE_MEMBLOCK_H__

/*
 * Memory map description
 */
# define NR_BANKS 8

struct membank {
	unsigned long start;
	unsigned long size;
	unsigned int highmem;
};

struct meminfo {
	int nr_banks;
	struct membank bank[NR_BANKS];
};

extern struct meminfo meminfo;

#define for_each_bank(iter, mi)				\
	for (iter = 0; iter < (mi)->nr_banks; iter++)

#define bank_pfn_start(bank)	__phys_to_pfn((bank)->start)
#define bank_pfn_end(bank)	__phys_to_pfn((bank)->start + (bank)->size)
#define bank_pfn_size(bank)	((bank)->size >> PAGE_SHIFT)
#define bank_phys_start(bank)	((bank)->start)
#define bank_phys_end(bank)	((bank)->start + (bank)->size)
#define bank_phys_size(bank)	((bank)->size)

extern void uc32_memblock_init(struct meminfo *);

#endif
