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
#include <beep/init.h>

#include <asm/tlbflush.h>
#include <asm/mmu_context.h>

mm_context_t next_mmu_context;
unsigned long context_map[LAST_CONTEXT / BITS_PER_LONG + 1];
atomic_t nr_free_contexts;
struct mm_struct *context_mm[LAST_CONTEXT+1];

/*
 * Initialize the context management stuff.
 */
void __init mmu_context_init(void)
{
	/*
	 * The use of context zero is reserved for the kernel.
	 * This code assumes FIRST_CONTEXT < 32.
	 */
	context_map[0] = (1 << FIRST_CONTEXT) - 1;
	next_mmu_context = FIRST_CONTEXT;
	atomic_set(&nr_free_contexts, LAST_CONTEXT - FIRST_CONTEXT + 1);
}

/*
 * Steal a context from a task that has one at the moment.
 *
 * This isn't an LRU system, it just frees up each context in
 * turn (sort-of pseudo-random replacement :).  This would be the
 * place to implement an LRU scheme if anyone were motivated to do it.
 */
void steal_context(void)
{
	struct mm_struct *mm;

	/* free up context `next_mmu_context' */
	/* if we shouldn't free context 0, don't... */
	if (next_mmu_context < FIRST_CONTEXT)
		next_mmu_context = FIRST_CONTEXT;
	mm = context_mm[next_mmu_context];
	flush_tlb_mm(mm);
	destroy_context(mm);
}
