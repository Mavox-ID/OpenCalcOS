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
#ifndef __ARCH_SPARC_ATOMIC__
#define __ARCH_SPARC_ATOMIC__

#include <beep/types.h>

#include <asm/cmpxchg.h>
#include <asm-generic/atomic64.h>


#define ATOMIC_INIT(i)  { (i) }

extern int __atomic_add_return(int, atomic_t *);
extern int atomic_cmpxchg(atomic_t *, int, int);
#define atomic_xchg(v, new) (xchg(&((v)->counter), new))
extern int __atomic_add_unless(atomic_t *, int, int);
extern void atomic_set(atomic_t *, int);

#define atomic_read(v)          (*(volatile int *)&(v)->counter)

#define atomic_add(i, v)	((void)__atomic_add_return( (int)(i), (v)))
#define atomic_sub(i, v)	((void)__atomic_add_return(-(int)(i), (v)))
#define atomic_inc(v)		((void)__atomic_add_return(        1, (v)))
#define atomic_dec(v)		((void)__atomic_add_return(       -1, (v)))

#define atomic_add_return(i, v)	(__atomic_add_return( (int)(i), (v)))
#define atomic_sub_return(i, v)	(__atomic_add_return(-(int)(i), (v)))
#define atomic_inc_return(v)	(__atomic_add_return(        1, (v)))
#define atomic_dec_return(v)	(__atomic_add_return(       -1, (v)))

#define atomic_add_negative(a, v)	(atomic_add_return((a), (v)) < 0)

/*
 * atomic_inc_and_test - increment and test
 * @v: pointer of type atomic_t
 *
 * Atomically increments @v by 1
 * and returns true if the result is zero, or false for all
 * other cases.
 */
#define atomic_inc_and_test(v) (atomic_inc_return(v) == 0)

#define atomic_dec_and_test(v) (atomic_dec_return(v) == 0)
#define atomic_sub_and_test(i, v) (atomic_sub_return(i, v) == 0)

/* Atomic operations are already serializing */
#define smp_mb__before_atomic_dec()	barrier()
#define smp_mb__after_atomic_dec()	barrier()
#define smp_mb__before_atomic_inc()	barrier()
#define smp_mb__after_atomic_inc()	barrier()

#endif /* !(__ARCH_SPARC_ATOMIC__) */
