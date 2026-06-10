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
#include <beep/module.h>
#include <beep/smp.h>

#include <net/checksum.h>

#include <asm/processor.h>
#include <asm/pgtable.h>
#include <asm/uaccess.h>
#include <asm/desc.h>
#include <asm/ftrace.h>

#ifdef CONFIG_FUNCTION_TRACER
/* mcount and __fentry__ are defined in assembly */
#ifdef CC_USING_FENTRY
EXPORT_SYMBOL(__fentry__);
#else
EXPORT_SYMBOL(mcount);
#endif
#endif

EXPORT_SYMBOL(__get_user_1);
EXPORT_SYMBOL(__get_user_2);
EXPORT_SYMBOL(__get_user_4);
EXPORT_SYMBOL(__get_user_8);
EXPORT_SYMBOL(__put_user_1);
EXPORT_SYMBOL(__put_user_2);
EXPORT_SYMBOL(__put_user_4);
EXPORT_SYMBOL(__put_user_8);

EXPORT_SYMBOL(copy_user_generic_string);
EXPORT_SYMBOL(copy_user_generic_unrolled);
EXPORT_SYMBOL(copy_user_enhanced_fast_string);
EXPORT_SYMBOL(__copy_user_nocache);
EXPORT_SYMBOL(_copy_from_user);
EXPORT_SYMBOL(_copy_to_user);

EXPORT_SYMBOL(copy_page);
EXPORT_SYMBOL(clear_page);

EXPORT_SYMBOL(csum_partial);

/*
 * Export string functions. We normally rely on gcc builtin for most of these,
 * but gcc sometimes decides not to inline them.
 */
#undef memcpy
#undef memset
#undef memmove

extern void *memset(void *, int, __kernel_size_t);
extern void *memcpy(void *, const void *, __kernel_size_t);
extern void *__memcpy(void *, const void *, __kernel_size_t);

EXPORT_SYMBOL(memset);
EXPORT_SYMBOL(memcpy);
EXPORT_SYMBOL(__memcpy);
EXPORT_SYMBOL(memmove);

EXPORT_SYMBOL(empty_zero_page);
#ifndef CONFIG_PARAVIRT
EXPORT_SYMBOL(native_load_gs_index);
#endif
