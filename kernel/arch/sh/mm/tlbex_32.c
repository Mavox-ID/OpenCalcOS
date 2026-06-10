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
#include <beep/mm.h>
#include <beep/kprobes.h>
#include <beep/kdebug.h>
#include <asm/mmu_context.h>
#include <asm/thread_info.h>

/*
 * Called with interrupts disabled.
 */
asmlinkage int __kprobes
handle_tlbmiss(struct pt_regs *regs, unsigned long error_code,
	       unsigned long address)
{
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	pte_t entry;

	/*
	 * We don't take page faults for P1, P2, and parts of P4, these
	 * are always mapped, whether it be due to legacy behaviour in
	 * 29-bit mode, or due to PMB configuration in 32-bit mode.
	 */
	if (address >= P3SEG && address < P3_ADDR_MAX) {
		pgd = pgd_offset_k(address);
	} else {
		if (unlikely(address >= TASK_SIZE || !current->mm))
			return 1;

		pgd = pgd_offset(current->mm, address);
	}

	pud = pud_offset(pgd, address);
	if (pud_none_or_clear_bad(pud))
		return 1;
	pmd = pmd_offset(pud, address);
	if (pmd_none_or_clear_bad(pmd))
		return 1;
	pte = pte_offset_kernel(pmd, address);
	entry = *pte;
	if (unlikely(pte_none(entry) || pte_not_present(entry)))
		return 1;
	if (unlikely(error_code && !pte_write(entry)))
		return 1;

	if (error_code)
		entry = pte_mkdirty(entry);
	entry = pte_mkyoung(entry);

	set_pte(pte, entry);

#if defined(CONFIG_CPU_SH4) && !defined(CONFIG_SMP)
	/*
	 * SH-4 does not set MMUCR.RC to the corresponding TLB entry in
	 * the case of an initial page write exception, so we need to
	 * flush it in order to avoid potential TLB entry duplication.
	 */
	if (error_code == FAULT_CODE_INITIAL)
		local_flush_tlb_one(get_asid(), address & PAGE_MASK);
#endif

	set_thread_fault_code(error_code);
	update_mmu_cache(NULL, address, pte);

	return 0;
}
