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
#include <beep/kernel.h>
#include <beep/spinlock.h>
#include <beep/atomic.h>

#ifdef CONFIG_SMP
arch_spinlock_t __atomic_hash[ATOMIC_HASH_SIZE] __lock_aligned = {
	[0 ... (ATOMIC_HASH_SIZE-1)]  = __ARCH_SPIN_LOCK_UNLOCKED
};
#endif

#ifdef CONFIG_64BIT
unsigned long __xchg64(unsigned long x, unsigned long *ptr)
{
	unsigned long temp, flags;

	_atomic_spin_lock_irqsave(ptr, flags);
	temp = *ptr;
	*ptr = x;
	_atomic_spin_unlock_irqrestore(ptr, flags);
	return temp;
}
#endif

unsigned long __xchg32(int x, int *ptr)
{
	unsigned long flags;
	long temp;

	_atomic_spin_lock_irqsave(ptr, flags);
	temp = (long) *ptr;	/* XXX - sign extension wanted? */
	*ptr = x;
	_atomic_spin_unlock_irqrestore(ptr, flags);
	return (unsigned long)temp;
}


unsigned long __xchg8(char x, char *ptr)
{
	unsigned long flags;
	long temp;

	_atomic_spin_lock_irqsave(ptr, flags);
	temp = (long) *ptr;	/* XXX - sign extension wanted? */
	*ptr = x;
	_atomic_spin_unlock_irqrestore(ptr, flags);
	return (unsigned long)temp;
}


#ifdef CONFIG_64BIT
unsigned long __cmpxchg_u64(volatile unsigned long *ptr, unsigned long old, unsigned long new)
{
	unsigned long flags;
	unsigned long prev;

	_atomic_spin_lock_irqsave(ptr, flags);
	if ((prev = *ptr) == old)
		*ptr = new;
	_atomic_spin_unlock_irqrestore(ptr, flags);
	return prev;
}
#endif

unsigned long __cmpxchg_u32(volatile unsigned int *ptr, unsigned int old, unsigned int new)
{
	unsigned long flags;
	unsigned int prev;

	_atomic_spin_lock_irqsave(ptr, flags);
	if ((prev = *ptr) == old)
		*ptr = new;
	_atomic_spin_unlock_irqrestore(ptr, flags);
	return (unsigned long)prev;
}
