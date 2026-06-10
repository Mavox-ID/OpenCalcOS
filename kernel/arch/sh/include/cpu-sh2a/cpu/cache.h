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
#ifndef __ASM_CPU_SH2A_CACHE_H
#define __ASM_CPU_SH2A_CACHE_H

#define L1_CACHE_SHIFT	4

#define SH_CACHE_VALID		1
#define SH_CACHE_UPDATED	2
#define SH_CACHE_COMBINED	4
#define SH_CACHE_ASSOC		8

#define CCR		0xfffc1000 /* CCR1 */
#define CCR2		0xfffc1004

/*
 * Most of the SH-2A CCR1 definitions resemble the SH-4 ones. All others not
 * listed here are reserved.
 */
#define CCR_CACHE_CB	0x0000	/* Hack */
#define CCR_CACHE_OCE	0x0001
#define CCR_CACHE_WT	0x0002
#define CCR_CACHE_OCI	0x0008	/* OCF */
#define CCR_CACHE_ICE	0x0100
#define CCR_CACHE_ICI	0x0800	/* ICF */

#define CACHE_IC_ADDRESS_ARRAY	0xf0000000
#define CACHE_OC_ADDRESS_ARRAY	0xf0800000

#define CCR_CACHE_ENABLE	(CCR_CACHE_OCE | CCR_CACHE_ICE)
#define CCR_CACHE_INVALIDATE	(CCR_CACHE_OCI | CCR_CACHE_ICI)
#define CCR_ICACHE_INVALIDATE	CCR_CACHE_ICI
#define CCR_OCACHE_INVALIDATE	CCR_CACHE_OCI
#define CACHE_PHYSADDR_MASK	0x1ffffc00

#endif /* __ASM_CPU_SH2A_CACHE_H */
