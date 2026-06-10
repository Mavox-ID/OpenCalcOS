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
#ifndef __BFIN_MEM_MAP_H__
#define __BFIN_MEM_MAP_H__

#include <mach/mem_map.h>

/* Every Blackfin so far has MMRs like this */
#ifndef COREMMR_BASE
# define COREMMR_BASE 0xFFE00000
#endif
#ifndef SYSMMR_BASE
# define SYSMMR_BASE  0xFFC00000
#endif

/* Every Blackfin so far has on-chip Scratch Pad SRAM like this */
#ifndef L1_SCRATCH_START
# define L1_SCRATCH_START  0xFFB00000
# define L1_SCRATCH_LENGTH 0x1000
#endif

/* Most parts lack on-chip L2 SRAM */
#ifndef L2_START
# define L2_START  0
# define L2_LENGTH 0
#endif

/* Most parts lack on-chip L1 ROM */
#ifndef L1_ROM_START
# define L1_ROM_START  0
# define L1_ROM_LENGTH 0
#endif

/* Allow wonky SMP ports to override this */
#ifndef GET_PDA_SAFE
# define GET_PDA_SAFE(preg) \
	preg.l = _cpu_pda; \
	preg.h = _cpu_pda;
# define GET_PDA(preg, dreg) GET_PDA_SAFE(preg)

# ifndef __ASSEMBLY__

static inline unsigned long get_l1_scratch_start_cpu(int cpu)
{
	return L1_SCRATCH_START;
}
static inline unsigned long get_l1_code_start_cpu(int cpu)
{
	return L1_CODE_START;
}
static inline unsigned long get_l1_data_a_start_cpu(int cpu)
{
	return L1_DATA_A_START;
}
static inline unsigned long get_l1_data_b_start_cpu(int cpu)
{
	return L1_DATA_B_START;
}
static inline unsigned long get_l1_scratch_start(void)
{
	return get_l1_scratch_start_cpu(0);
}
static inline unsigned long get_l1_code_start(void)
{
	return  get_l1_code_start_cpu(0);
}
static inline unsigned long get_l1_data_a_start(void)
{
	return get_l1_data_a_start_cpu(0);
}
static inline unsigned long get_l1_data_b_start(void)
{
	return get_l1_data_b_start_cpu(0);
}

# endif /* __ASSEMBLY__ */
#endif /* !GET_PDA_SAFE */

#endif
