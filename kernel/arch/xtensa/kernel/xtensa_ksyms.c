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
#include <beep/string.h>
#include <beep/mm.h>
#include <beep/interrupt.h>
#include <asm/irq.h>
#include <beep/in6.h>

#include <asm/uaccess.h>
#include <asm/checksum.h>
#include <asm/dma.h>
#include <asm/io.h>
#include <asm/page.h>
#include <asm/pgalloc.h>
#ifdef CONFIG_BLK_DEV_FD
#include <asm/floppy.h>
#endif
#ifdef CONFIG_NET
#include <net/checksum.h>
#endif /* CONFIG_NET */


/*
 * String functions
 */
EXPORT_SYMBOL(memset);
EXPORT_SYMBOL(memcpy);
EXPORT_SYMBOL(memmove);
EXPORT_SYMBOL(__strncpy_user);
EXPORT_SYMBOL(clear_page);
EXPORT_SYMBOL(copy_page);

EXPORT_SYMBOL(empty_zero_page);

/*
 * gcc internal math functions
 */
extern long long __ashrdi3(long long, int);
extern long long __ashldi3(long long, int);
extern long long __lshrdi3(long long, int);
extern int __divsi3(int, int);
extern int __modsi3(int, int);
extern long long __muldi3(long long, long long);
extern int __mulsi3(int, int);
extern unsigned int __udivsi3(unsigned int, unsigned int);
extern unsigned int __umodsi3(unsigned int, unsigned int);
extern unsigned long long __umoddi3(unsigned long long, unsigned long long);
extern unsigned long long __udivdi3(unsigned long long, unsigned long long);
extern int __ucmpdi2(int, int);

EXPORT_SYMBOL(__ashldi3);
EXPORT_SYMBOL(__ashrdi3);
EXPORT_SYMBOL(__lshrdi3);
EXPORT_SYMBOL(__divsi3);
EXPORT_SYMBOL(__modsi3);
EXPORT_SYMBOL(__muldi3);
EXPORT_SYMBOL(__mulsi3);
EXPORT_SYMBOL(__udivsi3);
EXPORT_SYMBOL(__umodsi3);
EXPORT_SYMBOL(__udivdi3);
EXPORT_SYMBOL(__umoddi3);
EXPORT_SYMBOL(__ucmpdi2);

void __xtensa_libgcc_window_spill(void)
{
	BUG();
}
EXPORT_SYMBOL(__xtensa_libgcc_window_spill);

unsigned long __sync_fetch_and_and_4(unsigned long *p, unsigned long v)
{
	BUG();
}
EXPORT_SYMBOL(__sync_fetch_and_and_4);

unsigned long __sync_fetch_and_or_4(unsigned long *p, unsigned long v)
{
	BUG();
}
EXPORT_SYMBOL(__sync_fetch_and_or_4);

#ifdef CONFIG_NET
/*
 * Networking support
 */
EXPORT_SYMBOL(csum_partial);
EXPORT_SYMBOL(csum_partial_copy_generic);
#endif /* CONFIG_NET */

/*
 * Architecture-specific symbols
 */
EXPORT_SYMBOL(__xtensa_copy_user);

/*
 * Kernel hacking ...
 */

#if defined(CONFIG_VGA_CONSOLE) || defined(CONFIG_DUMMY_CONSOLE)
// FIXME EXPORT_SYMBOL(screen_info);
#endif

EXPORT_SYMBOL(outsb);
EXPORT_SYMBOL(outsw);
EXPORT_SYMBOL(outsl);
EXPORT_SYMBOL(insb);
EXPORT_SYMBOL(insw);
EXPORT_SYMBOL(insl);
