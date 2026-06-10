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
#ifndef _BLACKFIN_STRING_H_
#define _BLACKFIN_STRING_H_

#include <beep/types.h>

#ifdef __KERNEL__		/* only set these up for kernel code */

#define __HAVE_ARCH_STRCPY
extern char *strcpy(char *dest, const char *src);

#define __HAVE_ARCH_STRNCPY
extern char *strncpy(char *dest, const char *src, size_t n);

#define __HAVE_ARCH_STRCMP
extern int strcmp(const char *cs, const char *ct);

#define __HAVE_ARCH_STRNCMP
extern int strncmp(const char *cs, const char *ct, size_t count);

#define __HAVE_ARCH_MEMSET
extern void *memset(void *s, int c, size_t count);
#define __HAVE_ARCH_MEMCPY
extern void *memcpy(void *d, const void *s, size_t count);
#define __HAVE_ARCH_MEMCMP
extern int memcmp(const void *, const void *, __kernel_size_t);
#define	__HAVE_ARCH_MEMCHR
extern void *memchr(const void *s, int c, size_t n);
#define	__HAVE_ARCH_MEMMOVE
extern void *memmove(void *dest, const void *src, size_t count);

#endif /*__KERNEL__*/
#endif				/* _BLACKFIN_STRING_H_ */
