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
#include <beep/pci.h>
#include <asm/machvec.h>
#include <asm/io.h>

/*
 * Copy data from IO memory space to "real" memory space.
 */
void memcpy_fromio(void *to, const volatile void __iomem *from, unsigned long count)
{
	/*
	 * Would it be worthwhile doing byte and long transfers first
	 * to try and get aligned?
	 */
#ifdef CONFIG_CPU_SH4
	if ((count >= 0x20) &&
	     (((u32)to & 0x1f) == 0) && (((u32)from & 0x3) == 0)) {
		int tmp2, tmp3, tmp4, tmp5, tmp6;

		__asm__ __volatile__(
			"1:			\n\t"
			"mov.l	@%7+, r0	\n\t"
			"mov.l	@%7+, %2	\n\t"
			"movca.l r0, @%0	\n\t"
			"mov.l	@%7+, %3	\n\t"
			"mov.l	@%7+, %4	\n\t"
			"mov.l	@%7+, %5	\n\t"
			"mov.l	@%7+, %6	\n\t"
			"mov.l	@%7+, r7	\n\t"
			"mov.l	@%7+, r0	\n\t"
			"mov.l	%2, @(0x04,%0)	\n\t"
			"mov	#0x20, %2	\n\t"
			"mov.l	%3, @(0x08,%0)	\n\t"
			"sub	%2, %1		\n\t"
			"mov.l	%4, @(0x0c,%0)	\n\t"
			"cmp/hi	%1, %2		! T if 32 > count	\n\t"
			"mov.l	%5, @(0x10,%0)	\n\t"
			"mov.l	%6, @(0x14,%0)	\n\t"
			"mov.l	r7, @(0x18,%0)	\n\t"
			"mov.l	r0, @(0x1c,%0)	\n\t"
			"bf.s	1b		\n\t"
			" add	#0x20, %0	\n\t"
			: "=&r" (to), "=&r" (count),
			  "=&r" (tmp2), "=&r" (tmp3), "=&r" (tmp4),
			  "=&r" (tmp5), "=&r" (tmp6), "=&r" (from)
			: "7"(from), "0" (to), "1" (count)
			: "r0", "r7", "t", "memory");
	}
#endif

	if ((((u32)to | (u32)from) & 0x3) == 0) {
		for (; count > 3; count -= 4) {
			*(u32 *)to = *(volatile u32 *)from;
			to += 4;
			from += 4;
		}
	}

	for (; count > 0; count--) {
		*(u8 *)to = *(volatile u8 *)from;
		to++;
		from++;
	}

	mb();
}
EXPORT_SYMBOL(memcpy_fromio);

/*
 * Copy data from "real" memory space to IO memory space.
 */
void memcpy_toio(volatile void __iomem *to, const void *from, unsigned long count)
{
	if ((((u32)to | (u32)from) & 0x3) == 0) {
		for ( ; count > 3; count -= 4) {
			*(volatile u32 *)to = *(u32 *)from;
			to += 4;
			from += 4;
		}
	}

	for (; count > 0; count--) {
		*(volatile u8 *)to = *(u8 *)from;
		to++;
		from++;
	}

	mb();
}
EXPORT_SYMBOL(memcpy_toio);

/*
 * "memset" on IO memory space.
 * This needs to be optimized.
 */
void memset_io(volatile void __iomem *dst, int c, unsigned long count)
{
        while (count) {
                count--;
                writeb(c, dst);
                dst++;
        }
}
EXPORT_SYMBOL(memset_io);
