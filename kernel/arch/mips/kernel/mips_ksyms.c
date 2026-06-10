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
#include <beep/interrupt.h>
#include <beep/export.h>
#include <asm/checksum.h>
#include <beep/mm.h>
#include <asm/uaccess.h>
#include <asm/ftrace.h>

extern void *__bzero(void *__s, size_t __count);
extern long __strncpy_from_user_nocheck_asm(char *__to,
                                            const char *__from, long __len);
extern long __strncpy_from_user_asm(char *__to, const char *__from,
                                    long __len);
extern long __strlen_user_nocheck_asm(const char *s);
extern long __strlen_user_asm(const char *s);
extern long __strnlen_user_nocheck_asm(const char *s);
extern long __strnlen_user_asm(const char *s);

/*
 * String functions
 */
EXPORT_SYMBOL(memset);
EXPORT_SYMBOL(memcpy);
EXPORT_SYMBOL(memmove);

/*
 * Functions that operate on entire pages.  Mostly used by memory management.
 */
EXPORT_SYMBOL(clear_page);
EXPORT_SYMBOL(copy_page);

/*
 * Userspace access stuff.
 */
EXPORT_SYMBOL(__copy_user);
EXPORT_SYMBOL(__copy_user_inatomic);
EXPORT_SYMBOL(__bzero);
EXPORT_SYMBOL(__strncpy_from_user_nocheck_asm);
EXPORT_SYMBOL(__strncpy_from_user_asm);
EXPORT_SYMBOL(__strlen_user_nocheck_asm);
EXPORT_SYMBOL(__strlen_user_asm);
EXPORT_SYMBOL(__strnlen_user_nocheck_asm);
EXPORT_SYMBOL(__strnlen_user_asm);

EXPORT_SYMBOL(csum_partial);
EXPORT_SYMBOL(csum_partial_copy_nocheck);
EXPORT_SYMBOL(__csum_partial_copy_user);

EXPORT_SYMBOL(invalid_pte_table);
#ifdef CONFIG_FUNCTION_TRACER
/* _mcount is defined in arch/mips/kernel/mcount.S */
EXPORT_SYMBOL(_mcount);
#endif
