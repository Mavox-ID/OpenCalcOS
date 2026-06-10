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
#ifndef __ASM_MACH_MIPS_CPU_FEATURE_OVERRIDES_H
#define __ASM_MACH_MIPS_CPU_FEATURE_OVERRIDES_H


/*
 * CPU feature overrides for MIPS boards
 */
#ifdef CONFIG_CPU_MIPS32
#define cpu_has_tlb		1
#define cpu_has_4kex		1
#define cpu_has_4k_cache	1
/* #define cpu_has_fpu		? */
/* #define cpu_has_32fpr	? */
#define cpu_has_counter		1
/* #define cpu_has_watch	? */
#define cpu_has_divec		1
#define cpu_has_vce		0
/* #define cpu_has_cache_cdex_p	? */
/* #define cpu_has_cache_cdex_s	? */
/* #define cpu_has_prefetch	? */
#define cpu_has_mcheck		1
/* #define cpu_has_ejtag	? */
#ifdef CONFIG_CPU_HAS_LLSC
#define cpu_has_llsc		1
#else
#define cpu_has_llsc		0
#endif
/* #define cpu_has_vtag_icache	? */
/* #define cpu_has_dc_aliases	? */
/* #define cpu_has_ic_fills_f_dc ? */
#define cpu_has_nofpuex		0
/* #define cpu_has_64bits	? */
/* #define cpu_has_64bit_zero_reg ? */
/* #define cpu_has_inclusive_pcaches ? */
#define cpu_icache_snoops_remote_store 1
#endif

#ifdef CONFIG_CPU_MIPS64
#define cpu_has_tlb		1
#define cpu_has_4kex		1
#define cpu_has_4k_cache	1
/* #define cpu_has_fpu		? */
/* #define cpu_has_32fpr	? */
#define cpu_has_counter		1
/* #define cpu_has_watch	? */
#define cpu_has_divec		1
#define cpu_has_vce		0
/* #define cpu_has_cache_cdex_p	? */
/* #define cpu_has_cache_cdex_s	? */
/* #define cpu_has_prefetch	? */
#define cpu_has_mcheck		1
/* #define cpu_has_ejtag	? */
#define cpu_has_llsc		1
/* #define cpu_has_vtag_icache	? */
/* #define cpu_has_dc_aliases	? */
/* #define cpu_has_ic_fills_f_dc ? */
#define cpu_has_nofpuex		0
/* #define cpu_has_64bits	? */
/* #define cpu_has_64bit_zero_reg ? */
/* #define cpu_has_inclusive_pcaches ? */
#define cpu_icache_snoops_remote_store 1
#endif

#endif /* __ASM_MACH_MIPS_CPU_FEATURE_OVERRIDES_H */
