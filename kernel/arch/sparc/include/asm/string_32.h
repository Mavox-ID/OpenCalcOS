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
#ifndef __SPARC_STRING_H__
#define __SPARC_STRING_H__

#include <asm/page.h>

/* Really, userland/ksyms should not see any of this stuff. */

#ifdef __KERNEL__

extern void __memmove(void *,const void *,__kernel_size_t);

#ifndef EXPORT_SYMTAB_STROPS

/* First the mem*() things. */
#define __HAVE_ARCH_MEMMOVE
#undef memmove
#define memmove(_to, _from, _n) \
({ \
	void *_t = (_to); \
	__memmove(_t, (_from), (_n)); \
	_t; \
})

#define __HAVE_ARCH_MEMCPY
#define memcpy(t, f, n) __builtin_memcpy(t, f, n)

#define __HAVE_ARCH_MEMSET
#define memset(s, c, count) __builtin_memset(s, c, count)

#define __HAVE_ARCH_MEMSCAN

#undef memscan
#define memscan(__arg0, __char, __arg2)						\
({										\
	extern void *__memscan_zero(void *, size_t);				\
	extern void *__memscan_generic(void *, int, size_t);			\
	void *__retval, *__addr = (__arg0);					\
	size_t __size = (__arg2);						\
										\
	if(__builtin_constant_p(__char) && !(__char))				\
		__retval = __memscan_zero(__addr, __size);			\
	else									\
		__retval = __memscan_generic(__addr, (__char), __size);		\
										\
	__retval;								\
})

#define __HAVE_ARCH_MEMCMP
extern int memcmp(const void *,const void *,__kernel_size_t);

/* Now the str*() stuff... */
#define __HAVE_ARCH_STRLEN
extern __kernel_size_t strlen(const char *);

#define __HAVE_ARCH_STRNCMP
extern int strncmp(const char *, const char *, __kernel_size_t);

#endif /* !EXPORT_SYMTAB_STROPS */

#endif /* __KERNEL__ */

#endif /* !(__SPARC_STRING_H__) */
