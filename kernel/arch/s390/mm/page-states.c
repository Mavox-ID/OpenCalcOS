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
#include <beep/errno.h>
#include <beep/types.h>
#include <beep/mm.h>
#include <beep/gfp.h>
#include <beep/init.h>

#define ESSA_SET_STABLE		1
#define ESSA_SET_UNUSED		2

static int cmma_flag = 1;

static int __init cmma(char *str)
{
	char *parm;

	parm = strstrip(str);
	if (strcmp(parm, "yes") == 0 || strcmp(parm, "on") == 0) {
		cmma_flag = 1;
		return 1;
	}
	cmma_flag = 0;
	if (strcmp(parm, "no") == 0 || strcmp(parm, "off") == 0)
		return 1;
	return 0;
}
__setup("cmma=", cmma);

void __init cmma_init(void)
{
	register unsigned long tmp asm("0") = 0;
	register int rc asm("1") = -EOPNOTSUPP;

	if (!cmma_flag)
		return;
	asm volatile(
		"       .insn rrf,0xb9ab0000,%1,%1,0,0\n"
		"0:     la      %0,0\n"
		"1:\n"
		EX_TABLE(0b,1b)
		: "+&d" (rc), "+&d" (tmp));
	if (rc)
		cmma_flag = 0;
}

static inline void set_page_unstable(struct page *page, int order)
{
	int i, rc;

	for (i = 0; i < (1 << order); i++)
		asm volatile(".insn rrf,0xb9ab0000,%0,%1,%2,0"
			     : "=&d" (rc)
			     : "a" (page_to_phys(page + i)),
			       "i" (ESSA_SET_UNUSED));
}

void arch_free_page(struct page *page, int order)
{
	if (!cmma_flag)
		return;
	set_page_unstable(page, order);
}

static inline void set_page_stable(struct page *page, int order)
{
	int i, rc;

	for (i = 0; i < (1 << order); i++)
		asm volatile(".insn rrf,0xb9ab0000,%0,%1,%2,0"
			     : "=&d" (rc)
			     : "a" (page_to_phys(page + i)),
			       "i" (ESSA_SET_STABLE));
}

void arch_alloc_page(struct page *page, int order)
{
	if (!cmma_flag)
		return;
	set_page_stable(page, order);
}

void arch_set_page_states(int make_stable)
{
	unsigned long flags, order, t;
	struct list_head *l;
	struct page *page;
	struct zone *zone;

	if (!cmma_flag)
		return;
	if (make_stable)
		drain_local_pages(NULL);
	for_each_populated_zone(zone) {
		spin_lock_irqsave(&zone->lock, flags);
		for_each_migratetype_order(order, t) {
			list_for_each(l, &zone->free_area[order].free_list[t]) {
				page = list_entry(l, struct page, lru);
				if (make_stable)
					set_page_stable(page, order);
				else
					set_page_unstable(page, order);
			}
		}
		spin_unlock_irqrestore(&zone->lock, flags);
	}
}
