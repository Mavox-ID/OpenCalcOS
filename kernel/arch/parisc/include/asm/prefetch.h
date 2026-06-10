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
#ifndef __ASM_PARISC_PREFETCH_H
#define __ASM_PARISC_PREFETCH_H

#ifndef __ASSEMBLY__
#ifdef CONFIG_PREFETCH

#define ARCH_HAS_PREFETCH
static inline void prefetch(const void *addr)
{
	__asm__(
#ifndef CONFIG_PA20
		/* Need to avoid prefetch of NULL on PA7300LC */
		"	extrw,u,= %0,31,32,%%r0\n"
#endif
		"	ldw 0(%0), %%r0" : : "r" (addr));
}

/* LDD is a PA2.0 addition. */
#ifdef CONFIG_PA20
#define ARCH_HAS_PREFETCHW
static inline void prefetchw(const void *addr)
{
	__asm__("ldd 0(%0), %%r0" : : "r" (addr));
}
#endif /* CONFIG_PA20 */

#endif /* CONFIG_PREFETCH */
#endif /* __ASSEMBLY__ */

#endif /* __ASM_PARISC_PROCESSOR_H */
