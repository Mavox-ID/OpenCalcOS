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
#ifndef __ASM_MACH_LOONGSON_CPU_FEATURE_OVERRIDES_H
#define __ASM_MACH_LOONGSON_CPU_FEATURE_OVERRIDES_H

#define cpu_dcache_line_size()	32
#define cpu_icache_line_size()	32
#define cpu_scache_line_size()	32


#define cpu_has_32fpr		1
#define cpu_has_3k_cache	0
#define cpu_has_4k_cache	1
#define cpu_has_4kex		1
#define cpu_has_64bits		1
#define cpu_has_cache_cdex_p	0
#define cpu_has_cache_cdex_s	0
#define cpu_has_counter		1
#define cpu_has_dc_aliases	(PAGE_SIZE < 0x4000)
#define cpu_has_divec		0
#define cpu_has_dsp		0
#define cpu_has_dsp2		0
#define cpu_has_ejtag		0
#define cpu_has_fpu		1
#define cpu_has_ic_fills_f_dc	0
#define cpu_has_inclusive_pcaches	1
#define cpu_has_llsc 		1
#define cpu_has_mcheck		0
#define cpu_has_mdmx		0
#define cpu_has_mips16		0
#define cpu_has_mips32r1	0
#define cpu_has_mips32r2	0
#define cpu_has_mips3d		0
#define cpu_has_mips64r1	0
#define cpu_has_mips64r2	0
#define cpu_has_mipsmt		0
#define cpu_has_prefetch	0
#define cpu_has_smartmips	0
#define cpu_has_tlb		1
#define cpu_has_tx39_cache	0
#define cpu_has_userlocal	0
#define cpu_has_vce		0
#define cpu_has_veic		0
#define cpu_has_vint		0
#define cpu_has_vtag_icache	0
#define cpu_has_watch		1

#endif /* __ASM_MACH_LOONGSON_CPU_FEATURE_OVERRIDES_H */
