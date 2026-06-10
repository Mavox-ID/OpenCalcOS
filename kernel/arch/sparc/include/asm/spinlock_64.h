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
#ifndef __SPARC64_SPINLOCK_H
#define __SPARC64_SPINLOCK_H

#ifndef __ASSEMBLY__

/* To get debugging spinlocks which detect and catch
 * deadlock situations, set CONFIG_DEBUG_SPINLOCK
 * and rebuild your kernel.
 */

/* Because we play games to save cycles in the non-contention case, we
 * need to be extra careful about branch targets into the "spinning"
 * code.  They live in their own section, but the newer V9 branches
 * have a shorter range than the traditional 32-bit sparc branch
 * variants.  The rule is that the branches that go into and out of
 * the spinner sections must be pre-V9 branches.
 */

#define arch_spin_is_locked(lp)	((lp)->lock != 0)

#define arch_spin_unlock_wait(lp)	\
	do {	rmb();			\
	} while((lp)->lock)

static inline void arch_spin_lock(arch_spinlock_t *lock)
{
	unsigned long tmp;

	__asm__ __volatile__(
"1:	ldstub		[%1], %0\n"
"	brnz,pn		%0, 2f\n"
"	 nop\n"
"	.subsection	2\n"
"2:	ldub		[%1], %0\n"
"	brnz,pt		%0, 2b\n"
"	 nop\n"
"	ba,a,pt		%%xcc, 1b\n"
"	.previous"
	: "=&r" (tmp)
	: "r" (lock)
	: "memory");
}

static inline int arch_spin_trylock(arch_spinlock_t *lock)
{
	unsigned long result;

	__asm__ __volatile__(
"	ldstub		[%1], %0\n"
	: "=r" (result)
	: "r" (lock)
	: "memory");

	return (result == 0UL);
}

static inline void arch_spin_unlock(arch_spinlock_t *lock)
{
	__asm__ __volatile__(
"	stb		%%g0, [%0]"
	: /* No outputs */
	: "r" (lock)
	: "memory");
}

static inline void arch_spin_lock_flags(arch_spinlock_t *lock, unsigned long flags)
{
	unsigned long tmp1, tmp2;

	__asm__ __volatile__(
"1:	ldstub		[%2], %0\n"
"	brnz,pn		%0, 2f\n"
"	 nop\n"
"	.subsection	2\n"
"2:	rdpr		%%pil, %1\n"
"	wrpr		%3, %%pil\n"
"3:	ldub		[%2], %0\n"
"	brnz,pt		%0, 3b\n"
"	 nop\n"
"	ba,pt		%%xcc, 1b\n"
"	 wrpr		%1, %%pil\n"
"	.previous"
	: "=&r" (tmp1), "=&r" (tmp2)
	: "r"(lock), "r"(flags)
	: "memory");
}

/* Multi-reader locks, these are much saner than the 32-bit Sparc ones... */

static void inline arch_read_lock(arch_rwlock_t *lock)
{
	unsigned long tmp1, tmp2;

	__asm__ __volatile__ (
"1:	ldsw		[%2], %0\n"
"	brlz,pn		%0, 2f\n"
"4:	 add		%0, 1, %1\n"
"	cas		[%2], %0, %1\n"
"	cmp		%0, %1\n"
"	bne,pn		%%icc, 1b\n"
"	 nop\n"
"	.subsection	2\n"
"2:	ldsw		[%2], %0\n"
"	brlz,pt		%0, 2b\n"
"	 nop\n"
"	ba,a,pt		%%xcc, 4b\n"
"	.previous"
	: "=&r" (tmp1), "=&r" (tmp2)
	: "r" (lock)
	: "memory");
}

static int inline arch_read_trylock(arch_rwlock_t *lock)
{
	int tmp1, tmp2;

	__asm__ __volatile__ (
"1:	ldsw		[%2], %0\n"
"	brlz,a,pn	%0, 2f\n"
"	 mov		0, %0\n"
"	add		%0, 1, %1\n"
"	cas		[%2], %0, %1\n"
"	cmp		%0, %1\n"
"	bne,pn		%%icc, 1b\n"
"	 mov		1, %0\n"
"2:"
	: "=&r" (tmp1), "=&r" (tmp2)
	: "r" (lock)
	: "memory");

	return tmp1;
}

static void inline arch_read_unlock(arch_rwlock_t *lock)
{
	unsigned long tmp1, tmp2;

	__asm__ __volatile__(
"1:	lduw	[%2], %0\n"
"	sub	%0, 1, %1\n"
"	cas	[%2], %0, %1\n"
"	cmp	%0, %1\n"
"	bne,pn	%%xcc, 1b\n"
"	 nop"
	: "=&r" (tmp1), "=&r" (tmp2)
	: "r" (lock)
	: "memory");
}

static void inline arch_write_lock(arch_rwlock_t *lock)
{
	unsigned long mask, tmp1, tmp2;

	mask = 0x80000000UL;

	__asm__ __volatile__(
"1:	lduw		[%2], %0\n"
"	brnz,pn		%0, 2f\n"
"4:	 or		%0, %3, %1\n"
"	cas		[%2], %0, %1\n"
"	cmp		%0, %1\n"
"	bne,pn		%%icc, 1b\n"
"	 nop\n"
"	.subsection	2\n"
"2:	lduw		[%2], %0\n"
"	brnz,pt		%0, 2b\n"
"	 nop\n"
"	ba,a,pt		%%xcc, 4b\n"
"	.previous"
	: "=&r" (tmp1), "=&r" (tmp2)
	: "r" (lock), "r" (mask)
	: "memory");
}

static void inline arch_write_unlock(arch_rwlock_t *lock)
{
	__asm__ __volatile__(
"	stw		%%g0, [%0]"
	: /* no outputs */
	: "r" (lock)
	: "memory");
}

static int inline arch_write_trylock(arch_rwlock_t *lock)
{
	unsigned long mask, tmp1, tmp2, result;

	mask = 0x80000000UL;

	__asm__ __volatile__(
"	mov		0, %2\n"
"1:	lduw		[%3], %0\n"
"	brnz,pn		%0, 2f\n"
"	 or		%0, %4, %1\n"
"	cas		[%3], %0, %1\n"
"	cmp		%0, %1\n"
"	bne,pn		%%icc, 1b\n"
"	 nop\n"
"	mov		1, %2\n"
"2:"
	: "=&r" (tmp1), "=&r" (tmp2), "=&r" (result)
	: "r" (lock), "r" (mask)
	: "memory");

	return result;
}

#define arch_read_lock_flags(p, f) arch_read_lock(p)
#define arch_write_lock_flags(p, f) arch_write_lock(p)

#define arch_read_can_lock(rw)		(!((rw)->lock & 0x80000000UL))
#define arch_write_can_lock(rw)	(!(rw)->lock)

#define arch_spin_relax(lock)	cpu_relax()
#define arch_read_relax(lock)	cpu_relax()
#define arch_write_relax(lock)	cpu_relax()

#endif /* !(__ASSEMBLY__) */

#endif /* !(__SPARC64_SPINLOCK_H) */
