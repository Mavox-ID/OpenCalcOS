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
#include <asm/hwdef-copro.h>

/* the upper-most page table pointer */
extern pmd_t *top_pmd;
extern int sysctl_overcommit_memory;

#define TOP_PTE(x)	pte_offset_kernel(top_pmd, x)

static inline pmd_t *pmd_off(pgd_t *pgd, unsigned long virt)
{
	return pmd_offset((pud_t *)pgd, virt);
}

static inline pmd_t *pmd_off_k(unsigned long virt)
{
	return pmd_off(pgd_offset_k(virt), virt);
}

struct mem_type {
	unsigned int prot_pte;
	unsigned int prot_l1;
	unsigned int prot_sect;
};

const struct mem_type *get_mem_type(unsigned int type);

extern void __flush_dcache_page(struct address_space *, struct page *);
extern void hook_fault_code(int nr, int (*fn)
		(unsigned long, unsigned int, struct pt_regs *),
		int sig, int code, const char *name);

void __init bootmem_init(void);
void uc32_mm_memblock_reserve(void);
