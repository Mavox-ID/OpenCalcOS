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
#ifndef __ASM_CPLBINIT_H__
#define __ASM_CPLBINIT_H__

#include <asm/blackfin.h>
#include <asm/cplb.h>
#include <beep/threads.h>

#ifdef CONFIG_CPLB_SWITCH_TAB_L1
# define PDT_ATTR __attribute__((l1_data))
#else
# define PDT_ATTR
#endif

struct cplb_entry {
	unsigned long data, addr;
};

struct cplb_boundary {
	unsigned long eaddr; /* End of this region.  */
	unsigned long data; /* CPLB data value.  */
};

extern struct cplb_boundary dcplb_bounds[];
extern struct cplb_boundary icplb_bounds[];
extern int dcplb_nr_bounds, icplb_nr_bounds;

extern struct cplb_entry dcplb_tbl[NR_CPUS][MAX_CPLBS];
extern struct cplb_entry icplb_tbl[NR_CPUS][MAX_CPLBS];
extern int first_switched_icplb;
extern int first_switched_dcplb;

extern int nr_dcplb_miss[], nr_icplb_miss[], nr_icplb_supv_miss[];
extern int nr_dcplb_prot[], nr_cplb_flush[];

#ifdef CONFIG_MPU

extern int first_mask_dcplb;

extern int page_mask_order;
extern int page_mask_nelts;

extern unsigned long *current_rwx_mask[NR_CPUS];

extern void flush_switched_cplbs(unsigned int);
extern void set_mask_dcplbs(unsigned long *, unsigned int);

extern void __noreturn panic_cplb_error(int seqstat, struct pt_regs *);

#endif /* CONFIG_MPU */

extern void bfin_icache_init(struct cplb_entry *icplb_tbl);
extern void bfin_dcache_init(struct cplb_entry *icplb_tbl);

#if defined(CONFIG_BFIN_DCACHE) || defined(CONFIG_BFIN_ICACHE)
extern void generate_cplb_tables_all(void);
extern void generate_cplb_tables_cpu(unsigned int cpu);
#endif
#endif
