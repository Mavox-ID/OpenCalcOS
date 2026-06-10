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
#ifndef __ASM_CRIS_ATOMIC__
#define __ASM_CRIS_ATOMIC__

#include <beep/compiler.h>
#include <beep/types.h>
#include <asm/cmpxchg.h>
#include <arch/atomic.h>

/*
 * Atomic operations that C can't guarantee us.  Useful for
 * resource counting etc..
 */

#define ATOMIC_INIT(i)  { (i) }

#define atomic_read(v) (*(volatile int *)&(v)->counter)
#define atomic_set(v,i) (((v)->counter) = (i))

/* These should be written in asm but we do it in C for now. */

static inline void atomic_add(int i, volatile atomic_t *v)
{
	unsigned long flags;
	cris_atomic_save(v, flags);
	v->counter += i;
	cris_atomic_restore(v, flags);
}

static inline void atomic_sub(int i, volatile atomic_t *v)
{
	unsigned long flags;
	cris_atomic_save(v, flags);
	v->counter -= i;
	cris_atomic_restore(v, flags);
}

static inline int atomic_add_return(int i, volatile atomic_t *v)
{
	unsigned long flags;
	int retval;
	cris_atomic_save(v, flags);
	retval = (v->counter += i);
	cris_atomic_restore(v, flags);
	return retval;
}

#define atomic_add_negative(a, v)	(atomic_add_return((a), (v)) < 0)

static inline int atomic_sub_return(int i, volatile atomic_t *v)
{
	unsigned long flags;
	int retval;
	cris_atomic_save(v, flags);
	retval = (v->counter -= i);
	cris_atomic_restore(v, flags);
	return retval;
}

static inline int atomic_sub_and_test(int i, volatile atomic_t *v)
{
	int retval;
	unsigned long flags;
	cris_atomic_save(v, flags);
	retval = (v->counter -= i) == 0;
	cris_atomic_restore(v, flags);
	return retval;
}

static inline void atomic_inc(volatile atomic_t *v)
{
	unsigned long flags;
	cris_atomic_save(v, flags);
	(v->counter)++;
	cris_atomic_restore(v, flags);
}

static inline void atomic_dec(volatile atomic_t *v)
{
	unsigned long flags;
	cris_atomic_save(v, flags);
	(v->counter)--;
	cris_atomic_restore(v, flags);
}

static inline int atomic_inc_return(volatile atomic_t *v)
{
	unsigned long flags;
	int retval;
	cris_atomic_save(v, flags);
	retval = ++(v->counter);
	cris_atomic_restore(v, flags);
	return retval;
}

static inline int atomic_dec_return(volatile atomic_t *v)
{
	unsigned long flags;
	int retval;
	cris_atomic_save(v, flags);
	retval = --(v->counter);
	cris_atomic_restore(v, flags);
	return retval;
}
static inline int atomic_dec_and_test(volatile atomic_t *v)
{
	int retval;
	unsigned long flags;
	cris_atomic_save(v, flags);
	retval = --(v->counter) == 0;
	cris_atomic_restore(v, flags);
	return retval;
}

static inline int atomic_inc_and_test(volatile atomic_t *v)
{
	int retval;
	unsigned long flags;
	cris_atomic_save(v, flags);
	retval = ++(v->counter) == 0;
	cris_atomic_restore(v, flags);
	return retval;
}

static inline int atomic_cmpxchg(atomic_t *v, int old, int new)
{
	int ret;
	unsigned long flags;

	cris_atomic_save(v, flags);
	ret = v->counter;
	if (likely(ret == old))
		v->counter = new;
	cris_atomic_restore(v, flags);
	return ret;
}

#define atomic_xchg(v, new) (xchg(&((v)->counter), new))

static inline int __atomic_add_unless(atomic_t *v, int a, int u)
{
	int ret;
	unsigned long flags;

	cris_atomic_save(v, flags);
	ret = v->counter;
	if (ret != u)
		v->counter += a;
	cris_atomic_restore(v, flags);
	return ret;
}

/* Atomic operations are already serializing */
#define smp_mb__before_atomic_dec()    barrier()
#define smp_mb__after_atomic_dec()     barrier()
#define smp_mb__before_atomic_inc()    barrier()
#define smp_mb__after_atomic_inc()     barrier()

#endif
