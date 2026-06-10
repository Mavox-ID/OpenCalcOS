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
#ifndef _BLACKFIN_BARRIER_H
#define _BLACKFIN_BARRIER_H

#include <asm/cache.h>

#define nop()  __asm__ __volatile__ ("nop;\n\t" : : )

/*
 * Force strict CPU ordering.
 */
#ifdef CONFIG_SMP

#ifdef __ARCH_SYNC_CORE_DCACHE
/* Force Core data cache coherence */
# define mb()	do { barrier(); smp_check_barrier(); smp_mark_barrier(); } while (0)
# define rmb()	do { barrier(); smp_check_barrier(); } while (0)
# define wmb()	do { barrier(); smp_mark_barrier(); } while (0)
# define read_barrier_depends()	do { barrier(); smp_check_barrier(); } while (0)
#else
# define mb()	barrier()
# define rmb()	barrier()
# define wmb()	barrier()
# define read_barrier_depends()	do { } while (0)
#endif

#else /* !CONFIG_SMP */

#define mb()	barrier()
#define rmb()	barrier()
#define wmb()	barrier()
#define read_barrier_depends()	do { } while (0)

#endif /* !CONFIG_SMP */

#define smp_mb()  mb()
#define smp_rmb() rmb()
#define smp_wmb() wmb()
#define set_mb(var, value) do { var = value; mb(); } while (0)
#define smp_read_barrier_depends()	read_barrier_depends()

#endif /* _BLACKFIN_BARRIER_H */
