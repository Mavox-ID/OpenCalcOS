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
#ifndef __ASM_CPU_SH3_MMU_CONTEXT_H
#define __ASM_CPU_SH3_MMU_CONTEXT_H

#define MMU_PTEH	0xFFFFFFF0	/* Page table entry register HIGH */
#define MMU_PTEL	0xFFFFFFF4	/* Page table entry register LOW */
#define MMU_TTB		0xFFFFFFF8	/* Translation table base register */
#define MMU_TEA		0xFFFFFFFC	/* TLB Exception Address */

#define MMUCR		0xFFFFFFE0	/* MMU Control Register */
#define MMUCR_TI	(1 << 2)	/* TLB flush bit */

#define MMU_TLB_ADDRESS_ARRAY	0xF2000000
#define MMU_PAGE_ASSOC_BIT	0x80

#define MMU_NTLB_ENTRIES	128	/* for 7708 */
#define MMU_NTLB_WAYS		4
#define MMU_CONTROL_INIT	0x007	/* SV=0, TF=1, IX=1, AT=1 */

#define TRA	0xffffffd0
#define EXPEVT	0xffffffd4

#if defined(CONFIG_CPU_SUBTYPE_SH7705) || \
    defined(CONFIG_CPU_SUBTYPE_SH7706) || \
    defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709) || \
    defined(CONFIG_CPU_SUBTYPE_SH7710) || \
    defined(CONFIG_CPU_SUBTYPE_SH7712) || \
    defined(CONFIG_CPU_SUBTYPE_SH7720) || \
    defined(CONFIG_CPU_SUBTYPE_SH7721)
#define INTEVT	0xa4000000	/* INTEVTE2(0xa4000000) */
#else
#define INTEVT	0xffffffd8
#endif

#endif /* __ASM_CPU_SH3_MMU_CONTEXT_H */

