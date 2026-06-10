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
#ifndef __ASM_CPU_SH3_CACHE_H
#define __ASM_CPU_SH3_CACHE_H

#define L1_CACHE_SHIFT	4

#define SH_CACHE_VALID		1
#define SH_CACHE_UPDATED	2
#define SH_CACHE_COMBINED	4
#define SH_CACHE_ASSOC		8

#define CCR		0xffffffec	/* Address of Cache Control Register */

#define CCR_CACHE_CE	0x01	/* Cache Enable */
#define CCR_CACHE_WT	0x02	/* Write-Through (for P0,U0,P3) (else writeback) */
#define CCR_CACHE_CB	0x04	/* Write-Back (for P1) (else writethrough) */
#define CCR_CACHE_CF	0x08	/* Cache Flush */
#define CCR_CACHE_ORA	0x20	/* RAM mode */

#define CACHE_OC_ADDRESS_ARRAY	0xf0000000
#define CACHE_PHYSADDR_MASK	0x1ffffc00

#define CCR_CACHE_ENABLE	CCR_CACHE_CE
#define CCR_CACHE_INVALIDATE	CCR_CACHE_CF

#if defined(CONFIG_CPU_SUBTYPE_SH7705) || \
    defined(CONFIG_CPU_SUBTYPE_SH7710) || \
    defined(CONFIG_CPU_SUBTYPE_SH7720) || \
    defined(CONFIG_CPU_SUBTYPE_SH7721)
#define CCR3_REG	0xa40000b4
#define CCR_CACHE_16KB  0x00010000
#define CCR_CACHE_32KB	0x00020000
#endif

#endif /* __ASM_CPU_SH3_CACHE_H */
