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
#ifndef __ARCH_SPARC64_CMPXCHG__
#define __ARCH_SPARC64_CMPXCHG__

static inline unsigned long xchg32(__volatile__ unsigned int *m, unsigned int val)
{
	unsigned long tmp1, tmp2;

	__asm__ __volatile__(
"	mov		%0, %1\n"
"1:	lduw		[%4], %2\n"
"	cas		[%4], %2, %0\n"
"	cmp		%2, %0\n"
"	bne,a,pn	%%icc, 1b\n"
"	 mov		%1, %0\n"
	: "=&r" (val), "=&r" (tmp1), "=&r" (tmp2)
	: "0" (val), "r" (m)
	: "cc", "memory");
	return val;
}

static inline unsigned long xchg64(__volatile__ unsigned long *m, unsigned long val)
{
	unsigned long tmp1, tmp2;

	__asm__ __volatile__(
"	mov		%0, %1\n"
"1:	ldx		[%4], %2\n"
"	casx		[%4], %2, %0\n"
"	cmp		%2, %0\n"
"	bne,a,pn	%%xcc, 1b\n"
"	 mov		%1, %0\n"
	: "=&r" (val), "=&r" (tmp1), "=&r" (tmp2)
	: "0" (val), "r" (m)
	: "cc", "memory");
	return val;
}

#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))

extern void __xchg_called_with_bad_pointer(void);

static inline unsigned long __xchg(unsigned long x, __volatile__ void * ptr,
				       int size)
{
	switch (size) {
	case 4:
		return xchg32(ptr, x);
	case 8:
		return xchg64(ptr, x);
	}
	__xchg_called_with_bad_pointer();
	return x;
}

/*
 * Atomic compare and exchange.  Compare OLD with MEM, if identical,
 * store NEW in MEM.  Return the initial value in MEM.  Success is
 * indicated by comparing RETURN with OLD.
 */

#include <asm-generic/cmpxchg-local.h>

#define __HAVE_ARCH_CMPXCHG 1

static inline unsigned long
__cmpxchg_u32(volatile int *m, int old, int new)
{
	__asm__ __volatile__("cas [%2], %3, %0"
			     : "=&r" (new)
			     : "0" (new), "r" (m), "r" (old)
			     : "memory");

	return new;
}

static inline unsigned long
__cmpxchg_u64(volatile long *m, unsigned long old, unsigned long new)
{
	__asm__ __volatile__("casx [%2], %3, %0"
			     : "=&r" (new)
			     : "0" (new), "r" (m), "r" (old)
			     : "memory");

	return new;
}

/* This function doesn't exist, so you'll get a linker error
   if something tries to do an invalid cmpxchg().  */
extern void __cmpxchg_called_with_bad_pointer(void);

static inline unsigned long
__cmpxchg(volatile void *ptr, unsigned long old, unsigned long new, int size)
{
	switch (size) {
		case 4:
			return __cmpxchg_u32(ptr, old, new);
		case 8:
			return __cmpxchg_u64(ptr, old, new);
	}
	__cmpxchg_called_with_bad_pointer();
	return old;
}

#define cmpxchg(ptr,o,n)						 \
  ({									 \
     __typeof__(*(ptr)) _o_ = (o);					 \
     __typeof__(*(ptr)) _n_ = (n);					 \
     (__typeof__(*(ptr))) __cmpxchg((ptr), (unsigned long)_o_,		 \
				    (unsigned long)_n_, sizeof(*(ptr))); \
  })

/*
 * cmpxchg_local and cmpxchg64_local are atomic wrt current CPU. Always make
 * them available.
 */

static inline unsigned long __cmpxchg_local(volatile void *ptr,
				      unsigned long old,
				      unsigned long new, int size)
{
	switch (size) {
	case 4:
	case 8:	return __cmpxchg(ptr, old, new, size);
	default:
		return __cmpxchg_local_generic(ptr, old, new, size);
	}

	return old;
}

#define cmpxchg_local(ptr, o, n)				  	\
	((__typeof__(*(ptr)))__cmpxchg_local((ptr), (unsigned long)(o),	\
			(unsigned long)(n), sizeof(*(ptr))))
#define cmpxchg64_local(ptr, o, n)					\
  ({									\
	BUILD_BUG_ON(sizeof(*(ptr)) != 8);				\
	cmpxchg_local((ptr), (o), (n));					\
  })

#endif /* __ARCH_SPARC64_CMPXCHG__ */
