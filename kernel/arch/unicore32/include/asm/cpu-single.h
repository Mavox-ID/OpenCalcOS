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
#ifndef __UNICORE_CPU_SINGLE_H__
#define __UNICORE_CPU_SINGLE_H__

#include <asm/page.h>
#include <asm/memory.h>

#ifdef __KERNEL__
#ifndef __ASSEMBLY__

#define cpu_switch_mm(pgd, mm) cpu_do_switch_mm(virt_to_phys(pgd), mm)

#define cpu_get_pgd()					\
	({						\
		unsigned long pg;			\
		__asm__("movc	%0, p0.c2, #0"		\
			 : "=r" (pg) : : "cc");		\
		pg &= ~0x0fff;				\
		(pgd_t *)phys_to_virt(pg);		\
	})

struct mm_struct;

/* declare all the functions as extern */
extern void cpu_proc_fin(void);
extern int cpu_do_idle(void);
extern void cpu_dcache_clean_area(void *, int);
extern void cpu_do_switch_mm(unsigned long pgd_phys, struct mm_struct *mm);
extern void cpu_set_pte(pte_t *ptep, pte_t pte);
extern void cpu_reset(unsigned long addr) __attribute__((noreturn));

#endif /* __ASSEMBLY__ */
#endif /* __KERNEL__ */

#endif /* __UNICORE_CPU_SINGLE_H__ */
