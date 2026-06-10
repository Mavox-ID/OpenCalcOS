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
#ifndef _XTENSA_ASMMACRO_H
#define _XTENSA_ASMMACRO_H

#include <variant/core.h>

/*
 * Some little helpers for loops. Use zero-overhead-loops
 * where applicable and if supported by the processor.
 *
 * __loopi ar, at, size, inc
 *         ar	register initialized with the start address
 *	   at	scratch register used by macro
 *	   size	size immediate value
 *	   inc	increment
 *
 * __loops ar, as, at, inc_log2[, mask_log2][, cond][, ncond]
 *	   ar	register initialized with the start address
 *	   as	register initialized with the size
 *	   at	scratch register use by macro
 *	   inc_log2	increment [in log2]
 *	   mask_log2	mask [in log2]
 *	   cond		true condition (used in loop'cond')
 *	   ncond	false condition (used in b'ncond')
 *
 * __loop  as
 *	   restart loop. 'as' register must not have been modified!
 *
 * __endla ar, at, incr
 *	   ar	start address (modified)
 *	   as	scratch register used by macro
 *	   inc	increment
 */

/*
 * loop for given size as immediate
 */

	.macro	__loopi ar, at, size, incr

#if XCHAL_HAVE_LOOPS
		movi	\at, ((\size + \incr - 1) / (\incr))
		loop	\at, 99f
#else
		addi	\at, \ar, \size
		98:
#endif

	.endm

/*
 * loop for given size in register
 */

	.macro	__loops	ar, as, at, incr_log2, mask_log2, cond, ncond

#if XCHAL_HAVE_LOOPS
		.ifgt \incr_log2 - 1
			addi	\at, \as, (1 << \incr_log2) - 1
			.ifnc \mask_log2,
				extui	\at, \at, \incr_log2, \mask_log2
			.else
				srli	\at, \at, \incr_log2
			.endif
		.endif
		loop\cond	\at, 99f
#else
		.ifnc \mask_log2,
			extui	\at, \as, \incr_log2, \mask_log2
		.else
			.ifnc \ncond,
				srli	\at, \as, \incr_log2
			.endif
		.endif
		.ifnc \ncond,
			b\ncond	\at, 99f

		.endif
		.ifnc \mask_log2,
			slli	\at, \at, \incr_log2
			add	\at, \ar, \at
		.else
			add	\at, \ar, \as
		.endif
#endif
		98:

	.endm

/*
 * loop from ar to ax
 */

	.macro	__loopt	ar, as, at, incr_log2

#if XCHAL_HAVE_LOOPS
		sub	\at, \as, \ar
		.ifgt	\incr_log2 - 1
			addi	\at, \at, (1 << \incr_log2) - 1
			srli	\at, \at, \incr_log2
		.endif
		loop	\at, 99f
#else
		98:
#endif

	.endm

/*
 * restart loop. registers must be unchanged
 */

	.macro	__loop	as

#if XCHAL_HAVE_LOOPS
		loop	\as, 99f
#else
		98:
#endif

	.endm

/*
 * end of loop with no increment of the address.
 */

	.macro	__endl	ar, as
#if !XCHAL_HAVE_LOOPS
		bltu	\ar, \as, 98b
#endif
		99:
	.endm

/*
 * end of loop with increment of the address.
 */

	.macro	__endla	ar, as, incr
		addi	\ar, \ar, \incr
		__endl	\ar \as
	.endm


#endif /* _XTENSA_ASMMACRO_H */
