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
#include <beep/nmi.h>
#include <beep/quicklist.h>

void show_mem(unsigned int filter)
{
	pg_data_t *pgdat;
	unsigned long total = 0, reserved = 0, shared = 0,
		nonshared = 0, highmem = 0;

	printk("Mem-Info:\n");
	show_free_areas(filter);

	for_each_online_pgdat(pgdat) {
		unsigned long i, flags;

		pgdat_resize_lock(pgdat, &flags);
		for (i = 0; i < pgdat->node_spanned_pages; i++) {
			struct page *page;
			unsigned long pfn = pgdat->node_start_pfn + i;

			if (unlikely(!(i % MAX_ORDER_NR_PAGES)))
				touch_nmi_watchdog();

			if (!pfn_valid(pfn))
				continue;

			page = pfn_to_page(pfn);

			if (PageHighMem(page))
				highmem++;

			if (PageReserved(page))
				reserved++;
			else if (page_count(page) == 1)
				nonshared++;
			else if (page_count(page) > 1)
				shared += page_count(page) - 1;

			total++;
		}
		pgdat_resize_unlock(pgdat, &flags);
	}

	printk("%lu pages RAM\n", total);
#ifdef CONFIG_HIGHMEM
	printk("%lu pages HighMem\n", highmem);
#endif
	printk("%lu pages reserved\n", reserved);
	printk("%lu pages shared\n", shared);
	printk("%lu pages non-shared\n", nonshared);
#ifdef CONFIG_QUICKLIST
	printk("%lu pages in pagetable cache\n",
		quicklist_total_size());
#endif
}
