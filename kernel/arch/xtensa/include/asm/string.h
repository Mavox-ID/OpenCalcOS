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
/* We should optimize these. See arch/xtensa/lib/strncpy_user.S */

#ifndef _XTENSA_STRING_H
#define _XTENSA_STRING_H

#define __HAVE_ARCH_STRCPY
static inline char *strcpy(char *__dest, const char *__src)
{
	register char *__xdest = __dest;
	unsigned long __dummy;

	__asm__ __volatile__("1:\n\t"
		"l8ui	%2, %1, 0\n\t"
		"s8i	%2, %0, 0\n\t"
		"addi	%1, %1, 1\n\t"
		"addi	%0, %0, 1\n\t"
		"bnez	%2, 1b\n\t"
		: "=r" (__dest), "=r" (__src), "=&r" (__dummy)
		: "0" (__dest), "1" (__src)
		: "memory");

	return __xdest;
}

#define __HAVE_ARCH_STRNCPY
static inline char *strncpy(char *__dest, const char *__src, size_t __n)
{
	register char *__xdest = __dest;
	unsigned long __dummy;

	if (__n == 0)
		return __xdest;

	__asm__ __volatile__(
		"1:\n\t"
		"l8ui	%2, %1, 0\n\t"
		"s8i	%2, %0, 0\n\t"
		"addi	%1, %1, 1\n\t"
		"addi	%0, %0, 1\n\t"
		"beqz	%2, 2f\n\t"
		"bne	%1, %5, 1b\n"
		"2:"
		: "=r" (__dest), "=r" (__src), "=&r" (__dummy)
		: "0" (__dest), "1" (__src), "r" (__src+__n)
		: "memory");

	return __xdest;
}

#define __HAVE_ARCH_STRCMP
static inline int strcmp(const char *__cs, const char *__ct)
{
	register int __res;
	unsigned long __dummy;

	__asm__ __volatile__(
		"1:\n\t"
		"l8ui	%3, %1, 0\n\t"
		"addi	%1, %1, 1\n\t"
		"l8ui	%2, %0, 0\n\t"
		"addi	%0, %0, 1\n\t"
		"beqz	%2, 2f\n\t"
		"beq	%2, %3, 1b\n"
		"2:\n\t"
		"sub	%2, %3, %2"
		: "=r" (__cs), "=r" (__ct), "=&r" (__res), "=&r" (__dummy)
		: "0" (__cs), "1" (__ct));

	return __res;
}

#define __HAVE_ARCH_STRNCMP
static inline int strncmp(const char *__cs, const char *__ct, size_t __n)
{
	register int __res;
	unsigned long __dummy;

	__asm__ __volatile__(
		"mov	%2, %3\n"
		"1:\n\t"
		"beq	%0, %6, 2f\n\t"
		"l8ui	%3, %1, 0\n\t"
		"addi	%1, %1, 1\n\t"
		"l8ui	%2, %0, 0\n\t"
		"addi	%0, %0, 1\n\t"
		"beqz	%2, 2f\n\t"
		"beqz	%3, 2f\n\t"
		"beq	%2, %3, 1b\n"
		"2:\n\t"
		"sub	%2, %3, %2"
		: "=r" (__cs), "=r" (__ct), "=&r" (__res), "=&r" (__dummy)
		: "0" (__cs), "1" (__ct), "r" (__cs+__n));

	return __res;
}

#define __HAVE_ARCH_MEMSET
extern void *memset(void *__s, int __c, size_t __count);

#define __HAVE_ARCH_MEMCPY
extern void *memcpy(void *__to, __const__ void *__from, size_t __n);

#define __HAVE_ARCH_MEMMOVE
extern void *memmove(void *__dest, __const__ void *__src, size_t __n);

/* Don't build bcopy at all ...  */
#define __HAVE_ARCH_BCOPY

#endif	/* _XTENSA_STRING_H */
