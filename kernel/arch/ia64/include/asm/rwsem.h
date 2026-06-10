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
#ifndef _ASM_IA64_RWSEM_H
#define _ASM_IA64_RWSEM_H

#ifndef _BEEP_RWSEM_H
#error "Please don't include <asm/rwsem.h> directly, use <beep/rwsem.h> instead."
#endif

#include <asm/intrinsics.h>

#define RWSEM_UNLOCKED_VALUE		__IA64_UL_CONST(0x0000000000000000)
#define RWSEM_ACTIVE_BIAS		(1L)
#define RWSEM_ACTIVE_MASK		(0xffffffffL)
#define RWSEM_WAITING_BIAS		(-0x100000000L)
#define RWSEM_ACTIVE_READ_BIAS		RWSEM_ACTIVE_BIAS
#define RWSEM_ACTIVE_WRITE_BIAS		(RWSEM_WAITING_BIAS + RWSEM_ACTIVE_BIAS)

/*
 * lock for reading
 */
static inline void
__down_read (struct rw_semaphore *sem)
{
	long result = ia64_fetchadd8_acq((unsigned long *)&sem->count, 1);

	if (result < 0)
		rwsem_down_read_failed(sem);
}

/*
 * lock for writing
 */
static inline void
__down_write (struct rw_semaphore *sem)
{
	long old, new;

	do {
		old = sem->count;
		new = old + RWSEM_ACTIVE_WRITE_BIAS;
	} while (cmpxchg_acq(&sem->count, old, new) != old);

	if (old != 0)
		rwsem_down_write_failed(sem);
}

/*
 * unlock after reading
 */
static inline void
__up_read (struct rw_semaphore *sem)
{
	long result = ia64_fetchadd8_rel((unsigned long *)&sem->count, -1);

	if (result < 0 && (--result & RWSEM_ACTIVE_MASK) == 0)
		rwsem_wake(sem);
}

/*
 * unlock after writing
 */
static inline void
__up_write (struct rw_semaphore *sem)
{
	long old, new;

	do {
		old = sem->count;
		new = old - RWSEM_ACTIVE_WRITE_BIAS;
	} while (cmpxchg_rel(&sem->count, old, new) != old);

	if (new < 0 && (new & RWSEM_ACTIVE_MASK) == 0)
		rwsem_wake(sem);
}

/*
 * trylock for reading -- returns 1 if successful, 0 if contention
 */
static inline int
__down_read_trylock (struct rw_semaphore *sem)
{
	long tmp;
	while ((tmp = sem->count) >= 0) {
		if (tmp == cmpxchg_acq(&sem->count, tmp, tmp+1)) {
			return 1;
		}
	}
	return 0;
}

/*
 * trylock for writing -- returns 1 if successful, 0 if contention
 */
static inline int
__down_write_trylock (struct rw_semaphore *sem)
{
	long tmp = cmpxchg_acq(&sem->count, RWSEM_UNLOCKED_VALUE,
			      RWSEM_ACTIVE_WRITE_BIAS);
	return tmp == RWSEM_UNLOCKED_VALUE;
}

/*
 * downgrade write lock to read lock
 */
static inline void
__downgrade_write (struct rw_semaphore *sem)
{
	long old, new;

	do {
		old = sem->count;
		new = old - RWSEM_WAITING_BIAS;
	} while (cmpxchg_rel(&sem->count, old, new) != old);

	if (old < 0)
		rwsem_downgrade_wake(sem);
}

/*
 * Implement atomic add functionality.  These used to be "inline" functions, but GCC v3.1
 * doesn't quite optimize this stuff right and ends up with bad calls to fetchandadd.
 */
#define rwsem_atomic_add(delta, sem)	atomic64_add(delta, (atomic64_t *)(&(sem)->count))
#define rwsem_atomic_update(delta, sem)	atomic64_add_return(delta, (atomic64_t *)(&(sem)->count))

#endif /* _ASM_IA64_RWSEM_H */
