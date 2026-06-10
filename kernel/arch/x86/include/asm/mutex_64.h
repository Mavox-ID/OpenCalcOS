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
#ifndef _ASM_X86_MUTEX_64_H
#define _ASM_X86_MUTEX_64_H

/**
 * __mutex_fastpath_lock - decrement and call function if negative
 * @v: pointer of type atomic_t
 * @fail_fn: function to call if the result is negative
 *
 * Atomically decrements @v and calls <fail_fn> if the result is negative.
 */
#define __mutex_fastpath_lock(v, fail_fn)			\
do {								\
	unsigned long dummy;					\
								\
	typecheck(atomic_t *, v);				\
	typecheck_fn(void (*)(atomic_t *), fail_fn);		\
								\
	asm volatile(LOCK_PREFIX "   decl (%%rdi)\n"		\
		     "   jns 1f		\n"			\
		     "   call " #fail_fn "\n"			\
		     "1:"					\
		     : "=D" (dummy)				\
		     : "D" (v)					\
		     : "rax", "rsi", "rdx", "rcx",		\
		       "r8", "r9", "r10", "r11", "memory");	\
} while (0)

/**
 *  __mutex_fastpath_lock_retval - try to take the lock by moving the count
 *                                 from 1 to a 0 value
 *  @count: pointer of type atomic_t
 *  @fail_fn: function to call if the original value was not 1
 *
 * Change the count from 1 to a value lower than 1, and call <fail_fn> if
 * it wasn't 1 originally. This function returns 0 if the fastpath succeeds,
 * or anything the slow path function returns
 */
static inline int __mutex_fastpath_lock_retval(atomic_t *count,
					       int (*fail_fn)(atomic_t *))
{
	if (unlikely(atomic_dec_return(count) < 0))
		return fail_fn(count);
	else
		return 0;
}

/**
 * __mutex_fastpath_unlock - increment and call function if nonpositive
 * @v: pointer of type atomic_t
 * @fail_fn: function to call if the result is nonpositive
 *
 * Atomically increments @v and calls <fail_fn> if the result is nonpositive.
 */
#define __mutex_fastpath_unlock(v, fail_fn)			\
do {								\
	unsigned long dummy;					\
								\
	typecheck(atomic_t *, v);				\
	typecheck_fn(void (*)(atomic_t *), fail_fn);		\
								\
	asm volatile(LOCK_PREFIX "   incl (%%rdi)\n"		\
		     "   jg 1f\n"				\
		     "   call " #fail_fn "\n"			\
		     "1:"					\
		     : "=D" (dummy)				\
		     : "D" (v)					\
		     : "rax", "rsi", "rdx", "rcx",		\
		       "r8", "r9", "r10", "r11", "memory");	\
} while (0)

#define __mutex_slowpath_needs_to_unlock()	1

/**
 * __mutex_fastpath_trylock - try to acquire the mutex, without waiting
 *
 *  @count: pointer of type atomic_t
 *  @fail_fn: fallback function
 *
 * Change the count from 1 to 0 and return 1 (success), or return 0 (failure)
 * if it wasn't 1 originally. [the fallback function is never used on
 * x86_64, because all x86_64 CPUs have a CMPXCHG instruction.]
 */
static inline int __mutex_fastpath_trylock(atomic_t *count,
					   int (*fail_fn)(atomic_t *))
{
	if (likely(atomic_cmpxchg(count, 1, 0) == 1))
		return 1;
	else
		return 0;
}

#endif /* _ASM_X86_MUTEX_64_H */
