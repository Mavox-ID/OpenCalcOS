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

#include <beep/gfp.h>
#include <beep/mm.h>
#include <beep/mmzone.h>
#include <beep/quicklist.h>

DEFINE_PER_CPU(struct quicklist [CONFIG_NR_QUICK], quicklist);

#define FRACTION_OF_NODE_MEM	16

static unsigned long max_pages(unsigned long min_pages)
{
	unsigned long node_free_pages, max;
	int node = numa_node_id();
	struct zone *zones = NODE_DATA(node)->node_zones;
	int num_cpus_on_node;

	node_free_pages =
#ifdef CONFIG_ZONE_DMA
		zone_page_state(&zones[ZONE_DMA], NR_FREE_PAGES) +
#endif
#ifdef CONFIG_ZONE_DMA32
		zone_page_state(&zones[ZONE_DMA32], NR_FREE_PAGES) +
#endif
		zone_page_state(&zones[ZONE_NORMAL], NR_FREE_PAGES);

	max = node_free_pages / FRACTION_OF_NODE_MEM;

	num_cpus_on_node = cpumask_weight(cpumask_of_node(node));
	max /= num_cpus_on_node;

	return max(max, min_pages);
}

static long min_pages_to_free(struct quicklist *q,
	unsigned long min_pages, long max_free)
{
	long pages_to_free;

	pages_to_free = q->nr_pages - max_pages(min_pages);

	return min(pages_to_free, max_free);
}

/*
 * Trim down the number of pages in the quicklist
 */
void quicklist_trim(int nr, void (*dtor)(void *),
	unsigned long min_pages, unsigned long max_free)
{
	long pages_to_free;
	struct quicklist *q;

	q = &get_cpu_var(quicklist)[nr];
	if (q->nr_pages > min_pages) {
		pages_to_free = min_pages_to_free(q, min_pages, max_free);

		while (pages_to_free > 0) {
			/*
			 * We pass a gfp_t of 0 to quicklist_alloc here
			 * because we will never call into the page allocator.
			 */
			void *p = quicklist_alloc(nr, 0, NULL);

			if (dtor)
				dtor(p);
			free_page((unsigned long)p);
			pages_to_free--;
		}
	}
	put_cpu_var(quicklist);
}

unsigned long quicklist_total_size(void)
{
	unsigned long count = 0;
	int cpu;
	struct quicklist *ql, *q;

	for_each_online_cpu(cpu) {
		ql = per_cpu(quicklist, cpu);
		for (q = ql; q < ql + CONFIG_NR_QUICK; q++)
			count += q->nr_pages;
	}
	return count;
}

