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
#ifndef _ASM_IA64_BARRIER_H
#define _ASM_IA64_BARRIER_H

#include <beep/compiler.h>

/*
 * Macros to force memory ordering.  In these descriptions, "previous"
 * and "subsequent" refer to program order; "visible" means that all
 * architecturally visible effects of a memory access have occurred
 * (at a minimum, this means the memory has been read or written).
 *
 *   wmb():	Guarantees that all preceding stores to memory-
 *		like regions are visible before any subsequent
 *		stores and that all following stores will be
 *		visible only after all previous stores.
 *   rmb():	Like wmb(), but for reads.
 *   mb():	wmb()/rmb() combo, i.e., all previous memory
 *		accesses are visible before all subsequent
 *		accesses and vice versa.  This is also known as
 *		a "fence."
 *
 * Note: "mb()" and its variants cannot be used as a fence to order
 * accesses to memory mapped I/O registers.  For that, mf.a needs to
 * be used.  However, we don't want to always use mf.a because (a)
 * it's (presumably) much slower than mf and (b) mf.a is supported for
 * sequential memory pages only.
 */
#define mb()	ia64_mf()
#define rmb()	mb()
#define wmb()	mb()
#define read_barrier_depends()	do { } while(0)

#ifdef CONFIG_SMP
# define smp_mb()	mb()
# define smp_rmb()	rmb()
# define smp_wmb()	wmb()
# define smp_read_barrier_depends()	read_barrier_depends()
#else
# define smp_mb()	barrier()
# define smp_rmb()	barrier()
# define smp_wmb()	barrier()
# define smp_read_barrier_depends()	do { } while(0)
#endif

/*
 * XXX check on this ---I suspect what Linus really wants here is
 * acquire vs release semantics but we can't discuss this stuff with
 * Linus just yet.  Grrr...
 */
#define set_mb(var, value)	do { (var) = (value); mb(); } while (0)

/*
 * The group barrier in front of the rsm & ssm are necessary to ensure
 * that none of the previous instructions in the same group are
 * affected by the rsm/ssm.
 */

#endif /* _ASM_IA64_BARRIER_H */
