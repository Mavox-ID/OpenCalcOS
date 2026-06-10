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
#include <beep/signal.h>
#include <beep/sched.h>
#include <beep/kernel.h>
#include <beep/errno.h>
#include <beep/string.h>
#include <beep/types.h>
#include <beep/ptrace.h>
#include <beep/mman.h>
#include <beep/mm.h>
#include <beep/smp.h>
#include <beep/interrupt.h>
#include <beep/kprobes.h>
#include <asm/tlb.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/pgalloc.h>
#include <asm/mmu_context.h>

static int handle_tlbmiss(unsigned long long protection_flags,
			  unsigned long address)
{
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	pte_t entry;

	if (is_vmalloc_addr((void *)address)) {
		pgd = pgd_offset_k(address);
	} else {
		if (unlikely(address >= TASK_SIZE || !current->mm))
			return 1;

		pgd = pgd_offset(current->mm, address);
	}

	pud = pud_offset(pgd, address);
	if (pud_none(*pud) || !pud_present(*pud))
		return 1;

	pmd = pmd_offset(pud, address);
	if (pmd_none(*pmd) || !pmd_present(*pmd))
		return 1;

	pte = pte_offset_kernel(pmd, address);
	entry = *pte;
	if (pte_none(entry) || !pte_present(entry))
		return 1;

	/*
	 * If the page doesn't have sufficient protection bits set to
	 * service the kind of fault being handled, there's not much
	 * point doing the TLB refill.  Punt the fault to the general
	 * handler.
	 */
	if ((pte_val(entry) & protection_flags) != protection_flags)
		return 1;

	update_mmu_cache(NULL, address, pte);

	return 0;
}

/*
 * Put all this information into one structure so that everything is just
 * arithmetic relative to a single base address.  This reduces the number
 * of movi/shori pairs needed just to load addresses of static data.
 */
struct expevt_lookup {
	unsigned short protection_flags[8];
	unsigned char  is_text_access[8];
	unsigned char  is_write_access[8];
};

#define PRU (1<<9)
#define PRW (1<<8)
#define PRX (1<<7)
#define PRR (1<<6)

/* Sized as 8 rather than 4 to allow checking the PTE's PRU bit against whether
   the fault happened in user mode or privileged mode. */
static struct expevt_lookup expevt_lookup_table = {
	.protection_flags = {PRX, PRX, 0, 0, PRR, PRR, PRW, PRW},
	.is_text_access   = {1,   1,   0, 0, 0,   0,   0,   0}
};

static inline unsigned int
expevt_to_fault_code(unsigned long expevt)
{
	if (expevt == 0xa40)
		return FAULT_CODE_ITLB;
	else if (expevt == 0x060)
		return FAULT_CODE_WRITE;

	return 0;
}

/*
   This routine handles page faults that can be serviced just by refilling a
   TLB entry from an existing page table entry.  (This case represents a very
   large majority of page faults.) Return 1 if the fault was successfully
   handled.  Return 0 if the fault could not be handled.  (This leads into the
   general fault handling in fault.c which deals with mapping file-backed
   pages, stack growth, segmentation faults, swapping etc etc)
 */
asmlinkage int __kprobes
do_fast_page_fault(unsigned long long ssr_md, unsigned long long expevt,
		   unsigned long address)
{
	unsigned long long protection_flags;
	unsigned long long index;
	unsigned long long expevt4;
	unsigned int fault_code;

	/* The next few lines implement a way of hashing EXPEVT into a
	 * small array index which can be used to lookup parameters
	 * specific to the type of TLBMISS being handled.
	 *
	 * Note:
	 *	ITLBMISS has EXPEVT==0xa40
	 *	RTLBMISS has EXPEVT==0x040
	 *	WTLBMISS has EXPEVT==0x060
	 */
	expevt4 = (expevt >> 4);
	/* TODO : xor ssr_md into this expression too. Then we can check
	 * that PRU is set when it needs to be. */
	index = expevt4 ^ (expevt4 >> 5);
	index &= 7;

	fault_code = expevt_to_fault_code(expevt);

	protection_flags = expevt_lookup_table.protection_flags[index];

	if (expevt_lookup_table.is_text_access[index])
		fault_code |= FAULT_CODE_ITLB;
	if (!ssr_md)
		fault_code |= FAULT_CODE_USER;

	set_thread_fault_code(fault_code);

	return handle_tlbmiss(protection_flags, address);
}
