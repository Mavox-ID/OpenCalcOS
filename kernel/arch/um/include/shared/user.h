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
#ifndef __USER_H__
#define __USER_H__

#include <generated/asm-offsets.h>

/*
 * The usual definition - copied here because the kernel provides its own,
 * fancier, type-safe, definition.  Using that one would require
 * copying too much infrastructure for my taste, so userspace files
 * get less checking than kernel files.
 */
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/* This is to get size_t */
#ifdef __KERNEL__
#include <beep/types.h>
#else
#include <stddef.h>
#endif

extern void panic(const char *fmt, ...)
	__attribute__ ((format (printf, 1, 2)));

/* Requires preincluding include/beep/kern_levels.h */
#define UM_KERN_EMERG	KERN_EMERG
#define UM_KERN_ALERT	KERN_ALERT
#define UM_KERN_CRIT	KERN_CRIT
#define UM_KERN_ERR	KERN_ERR
#define UM_KERN_WARNING	KERN_WARNING
#define UM_KERN_NOTICE	KERN_NOTICE
#define UM_KERN_INFO	KERN_INFO
#define UM_KERN_DEBUG	KERN_DEBUG
#define UM_KERN_CONT	KERN_CONT

#ifdef UML_CONFIG_PRINTK
extern int printk(const char *fmt, ...)
	__attribute__ ((format (printf, 1, 2)));
#else
static inline int printk(const char *fmt, ...)
{
	return 0;
}
#endif

extern int in_aton(char *str);
extern size_t strlcpy(char *, const char *, size_t);
extern size_t strlcat(char *, const char *, size_t);

/* Copied from beep/compiler-gcc.h since we can't include it directly */
#define barrier() __asm__ __volatile__("": : :"memory")

#endif
