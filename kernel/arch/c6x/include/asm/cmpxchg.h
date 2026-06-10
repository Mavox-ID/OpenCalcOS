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
#ifndef _ASM_C6X_CMPXCHG_H
#define _ASM_C6X_CMPXCHG_H

#include <beep/irqflags.h>

/*
 * Misc. functions
 */
static inline unsigned int __xchg(unsigned int x, volatile void *ptr, int size)
{
	unsigned int tmp;
	unsigned long flags;

	local_irq_save(flags);

	switch (size) {
	case 1:
		tmp = 0;
		tmp = *((unsigned char *) ptr);
		*((unsigned char *) ptr) = (unsigned char) x;
		break;
	case 2:
		tmp = 0;
		tmp = *((unsigned short *) ptr);
		*((unsigned short *) ptr) = x;
		break;
	case 4:
		tmp = 0;
		tmp = *((unsigned int *) ptr);
		*((unsigned int *) ptr) = x;
		break;
	}
	local_irq_restore(flags);
	return tmp;
}

#define xchg(ptr, x) \
	((__typeof__(*(ptr)))__xchg((unsigned int)(x), (void *) (ptr), \
				    sizeof(*(ptr))))
#define tas(ptr)    xchg((ptr), 1)


#include <asm-generic/cmpxchg-local.h>

/*
 * cmpxchg_local and cmpxchg64_local are atomic wrt current CPU. Always make
 * them available.
 */
#define cmpxchg_local(ptr, o, n)					\
	((__typeof__(*(ptr)))__cmpxchg_local_generic((ptr),		\
						     (unsigned long)(o), \
						     (unsigned long)(n), \
						     sizeof(*(ptr))))
#define cmpxchg64_local(ptr, o, n) __cmpxchg64_local_generic((ptr), (o), (n))

#include <asm-generic/cmpxchg.h>

#endif /* _ASM_C6X_CMPXCHG_H */
