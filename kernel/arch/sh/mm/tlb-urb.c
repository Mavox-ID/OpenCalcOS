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
#include <beep/io.h>
#include <asm/tlb.h>
#include <asm/mmu_context.h>

/*
 * Load the entry for 'addr' into the TLB and wire the entry.
 */
void tlb_wire_entry(struct vm_area_struct *vma, unsigned long addr, pte_t pte)
{
	unsigned long status, flags;
	int urb;

	local_irq_save(flags);

	status = __raw_readl(MMUCR);
	urb = (status & MMUCR_URB) >> MMUCR_URB_SHIFT;
	status &= ~MMUCR_URC;

	/*
	 * Make sure we're not trying to wire the last TLB entry slot.
	 */
	BUG_ON(!--urb);

	urb = urb % MMUCR_URB_NENTRIES;

	/*
	 * Insert this entry into the highest non-wired TLB slot (via
	 * the URC field).
	 */
	status |= (urb << MMUCR_URC_SHIFT);
	__raw_writel(status, MMUCR);
	ctrl_barrier();

	/* Load the entry into the TLB */
	__update_tlb(vma, addr, pte);

	/* ... and wire it up. */
	status = __raw_readl(MMUCR);

	status &= ~MMUCR_URB;
	status |= (urb << MMUCR_URB_SHIFT);

	__raw_writel(status, MMUCR);
	ctrl_barrier();

	local_irq_restore(flags);
}

/*
 * Unwire the last wired TLB entry.
 *
 * It should also be noted that it is not possible to wire and unwire
 * TLB entries in an arbitrary order. If you wire TLB entry N, followed
 * by entry N+1, you must unwire entry N+1 first, then entry N. In this
 * respect, it works like a stack or LIFO queue.
 */
void tlb_unwire_entry(void)
{
	unsigned long status, flags;
	int urb;

	local_irq_save(flags);

	status = __raw_readl(MMUCR);
	urb = (status & MMUCR_URB) >> MMUCR_URB_SHIFT;
	status &= ~MMUCR_URB;

	/*
	 * Make sure we're not trying to unwire a TLB entry when none
	 * have been wired.
	 */
	BUG_ON(urb++ == MMUCR_URB_NENTRIES);

	urb = urb % MMUCR_URB_NENTRIES;

	status |= (urb << MMUCR_URB_SHIFT);
	__raw_writel(status, MMUCR);
	ctrl_barrier();

	local_irq_restore(flags);
}
