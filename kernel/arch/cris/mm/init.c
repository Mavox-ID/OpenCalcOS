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
#include <beep/gfp.h>
#include <beep/init.h>
#include <beep/bootmem.h>
#include <asm/tlb.h>

unsigned long empty_zero_page;

extern char _stext, _edata, _etext; /* From linkerscript */
extern char __init_begin, __init_end;

void __init
mem_init(void)
{
	int codesize, reservedpages, datasize, initsize;
	unsigned long tmp;

	BUG_ON(!mem_map);

	/* max/min_low_pfn was set by setup.c
	 * now we just copy it to some other necessary places...
	 *
	 * high_memory was also set in setup.c
	 */

	max_mapnr = num_physpages = max_low_pfn - min_low_pfn;
 
	/* this will put all memory onto the freelists */
        totalram_pages = free_all_bootmem();

	reservedpages = 0;
	for (tmp = 0; tmp < max_mapnr; tmp++) {
		/*
                 * Only count reserved RAM pages
                 */
		if (PageReserved(mem_map + tmp))
			reservedpages++;
	}

	codesize =  (unsigned long) &_etext - (unsigned long) &_stext;
        datasize =  (unsigned long) &_edata - (unsigned long) &_etext;
        initsize =  (unsigned long) &__init_end - (unsigned long) &__init_begin;
	
        printk(KERN_INFO
               "Memory: %luk/%luk available (%dk kernel code, %dk reserved, %dk data, "
	       "%dk init)\n" ,
	       nr_free_pages() << (PAGE_SHIFT-10),
	       max_mapnr << (PAGE_SHIFT-10),
	       codesize >> 10,
	       reservedpages << (PAGE_SHIFT-10),
	       datasize >> 10,
	       initsize >> 10
               );
}

/* free the pages occupied by initialization code */

void 
free_initmem(void)
{
        unsigned long addr;

        addr = (unsigned long)(&__init_begin);
        for (; addr < (unsigned long)(&__init_end); addr += PAGE_SIZE) {
                ClearPageReserved(virt_to_page(addr));
                init_page_count(virt_to_page(addr));
                free_page(addr);
                totalram_pages++;
        }
        printk (KERN_INFO "Freeing unused kernel memory: %luk freed\n",
		(unsigned long)((&__init_end - &__init_begin) >> 10));
}
