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
#ifndef __ASM_SH_TLB_64_H
#define __ASM_SH_TLB_64_H

/* ITLB defines */
#define ITLB_FIXED	0x00000000	/* First fixed ITLB, see head.S */
#define ITLB_LAST_VAR_UNRESTRICTED	0x000003F0	/* Last ITLB */

/* DTLB defines */
#define DTLB_FIXED	0x00800000	/* First fixed DTLB, see head.S */
#define DTLB_LAST_VAR_UNRESTRICTED	0x008003F0	/* Last DTLB */

#ifndef __ASSEMBLY__

/**
 * for_each_dtlb_entry - Iterate over free (non-wired) DTLB entries
 *
 * @tlb:	TLB entry
 */
#define for_each_dtlb_entry(tlb)		\
	for (tlb  = cpu_data->dtlb.first;	\
	     tlb <= cpu_data->dtlb.last;	\
	     tlb += cpu_data->dtlb.step)

/**
 * for_each_itlb_entry - Iterate over free (non-wired) ITLB entries
 *
 * @tlb:	TLB entry
 */
#define for_each_itlb_entry(tlb)		\
	for (tlb  = cpu_data->itlb.first;	\
	     tlb <= cpu_data->itlb.last;	\
	     tlb += cpu_data->itlb.step)

/**
 * __flush_tlb_slot - Flushes TLB slot @slot.
 *
 * @slot:	Address of TLB slot.
 */
static inline void __flush_tlb_slot(unsigned long long slot)
{
	__asm__ __volatile__ ("putcfg %0, 0, r63\n" : : "r" (slot));
}

#ifdef CONFIG_MMU
/* arch/sh64/mm/tlb.c */
int sh64_tlb_init(void);
unsigned long long sh64_next_free_dtlb_entry(void);
unsigned long long sh64_get_wired_dtlb_entry(void);
int sh64_put_wired_dtlb_entry(unsigned long long entry);
void sh64_setup_tlb_slot(unsigned long long config_addr, unsigned long eaddr,
			 unsigned long asid, unsigned long paddr);
void sh64_teardown_tlb_slot(unsigned long long config_addr);
#else
#define sh64_tlb_init()					do { } while (0)
#define sh64_next_free_dtlb_entry()			(0)
#define sh64_get_wired_dtlb_entry()			(0)
#define sh64_put_wired_dtlb_entry(entry)		do { } while (0)
#define sh64_setup_tlb_slot(conf, virt, asid, phys)	do { } while (0)
#define sh64_teardown_tlb_slot(addr)			do { } while (0)
#endif /* CONFIG_MMU */
#endif /* __ASSEMBLY__ */
#endif /* __ASM_SH_TLB_64_H */
