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
#ifndef __UNICORE_CMPXCHG_H__
#define __UNICORE_CMPXCHG_H__

/*
 * Generate a link failure on undefined symbol if the pointer points to a value
 * of unsupported size.
 */
extern void __xchg_bad_pointer(void);

static inline unsigned long __xchg(unsigned long x, volatile void *ptr,
		int size)
{
	unsigned long ret;

	switch (size) {
	case 1:
		asm volatile("swapb	%0, %1, [%2]"
			: "=&r" (ret)
			: "r" (x), "r" (ptr)
			: "memory", "cc");
		break;
	case 4:
		asm volatile("swapw	%0, %1, [%2]"
			: "=&r" (ret)
			: "r" (x), "r" (ptr)
			: "memory", "cc");
		break;
	default:
		__xchg_bad_pointer();
	}

	return ret;
}

#define xchg(ptr, x) \
	((__typeof__(*(ptr)))__xchg((unsigned long)(x), (ptr), sizeof(*(ptr))))

#include <asm-generic/cmpxchg-local.h>

/*
 * cmpxchg_local and cmpxchg64_local are atomic wrt current CPU. Always make
 * them available.
 */
#define cmpxchg_local(ptr, o, n)					\
		((__typeof__(*(ptr)))__cmpxchg_local_generic((ptr),	\
		(unsigned long)(o), (unsigned long)(n), sizeof(*(ptr))))
#define cmpxchg64_local(ptr, o, n)					\
		__cmpxchg64_local_generic((ptr), (o), (n))

#include <asm-generic/cmpxchg.h>

#endif /* __UNICORE_CMPXCHG_H__ */
