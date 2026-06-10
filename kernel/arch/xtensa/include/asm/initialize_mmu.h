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
#ifndef _XTENSA_INITIALIZE_MMU_H
#define _XTENSA_INITIALIZE_MMU_H

#ifdef __ASSEMBLY__

#define XTENSA_HWVERSION_RC_2009_0 230000

	.macro	initialize_mmu

#if XCHAL_HAVE_S32C1I && (XCHAL_HW_MIN_VERSION >= XTENSA_HWVERSION_RC_2009_0)
/*
 * We Have Atomic Operation Control (ATOMCTL) Register; Initialize it.
 * For details see Documentation/xtensa/atomctl.txt
 */
#if XCHAL_DCACHE_IS_COHERENT
	movi	a3, 0x25	/* For SMP/MX -- internal for writeback,
				 * RCW otherwise
				 */
#else
	movi	a3, 0x29	/* non-MX -- Most cores use Std Memory
				 * Controlers which usually can't use RCW
				 */
#endif
	wsr	a3, atomctl
#endif  /* XCHAL_HAVE_S32C1I &&
	 * (XCHAL_HW_MIN_VERSION >= XTENSA_HWVERSION_RC_2009_0)
	 */

	.endm

#endif /*__ASSEMBLY__*/

#endif /* _XTENSA_INITIALIZE_MMU_H */
