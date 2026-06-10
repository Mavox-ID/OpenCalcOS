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
#include <beep/init.h>

#include <asm/addrspace.h>
#include <asm/bug.h>
#include <asm/cacheflush.h>

#ifndef CKSEG2
#define CKSEG2 CKSSEG
#endif
#ifndef TO_PHYS_MASK
#define TO_PHYS_MASK -1
#endif

/*
 * FUNC is executed in one of the uncached segments, depending on its
 * original address as follows:
 *
 * 1. If the original address is in CKSEG0 or CKSEG1, then the uncached
 *    segment used is CKSEG1.
 * 2. If the original address is in XKPHYS, then the uncached segment
 *    used is XKPHYS(2).
 * 3. Otherwise it's a bug.
 *
 * The same remapping is done with the stack pointer.  Stack handling
 * works because we don't handle stack arguments or more complex return
 * values, so we can avoid sharing the same stack area between a cached
 * and the uncached mode.
 */
unsigned long __cpuinit run_uncached(void *func)
{
	register long sp __asm__("$sp");
	register long ret __asm__("$2");
	long lfunc = (long)func, ufunc;
	long usp;

	if (sp >= (long)CKSEG0 && sp < (long)CKSEG2)
		usp = CKSEG1ADDR(sp);
#ifdef CONFIG_64BIT
	else if ((long long)sp >= (long long)PHYS_TO_XKPHYS(0, 0) &&
		 (long long)sp < (long long)PHYS_TO_XKPHYS(8, 0))
		usp = PHYS_TO_XKPHYS(K_CALG_UNCACHED,
				     XKPHYS_TO_PHYS((long long)sp));
#endif
	else {
		BUG();
		usp = sp;
	}
	if (lfunc >= (long)CKSEG0 && lfunc < (long)CKSEG2)
		ufunc = CKSEG1ADDR(lfunc);
#ifdef CONFIG_64BIT
	else if ((long long)lfunc >= (long long)PHYS_TO_XKPHYS(0, 0) &&
		 (long long)lfunc < (long long)PHYS_TO_XKPHYS(8, 0))
		ufunc = PHYS_TO_XKPHYS(K_CALG_UNCACHED,
				       XKPHYS_TO_PHYS((long long)lfunc));
#endif
	else {
		BUG();
		ufunc = lfunc;
	}

	__asm__ __volatile__ (
		"	move	$16, $sp\n"
		"	move	$sp, %1\n"
		"	jalr	%2\n"
		"	move	$sp, $16"
		: "=r" (ret)
		: "r" (usp), "r" (ufunc)
		: "$16", "$31");

	return ret;
}
