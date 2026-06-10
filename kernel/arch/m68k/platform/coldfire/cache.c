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
/*
 *	cache.c -- general ColdFire Cache maintenance code
 *
 *	Copyright (C) 2010, Greg Ungerer (gerg@snapgear.com)
 */

/***************************************************************************/

#include <beep/kernel.h>
#include <asm/coldfire.h>
#include <asm/mcfsim.h>

/***************************************************************************/
#ifdef CACHE_PUSH
/***************************************************************************/

/*
 *	Use cpushl to push all dirty cache lines back to memory.
 *	Older versions of GAS don't seem to know how to generate the
 *	ColdFire cpushl instruction... Oh well, bit stuff it for now.
 */

void mcf_cache_push(void)
{
	__asm__ __volatile__ (
		"clrl	%%d0\n\t"
		"1:\n\t"
		"movel	%%d0,%%a0\n\t"
		"2:\n\t"
		".word	0xf468\n\t"
		"addl	%0,%%a0\n\t"
		"cmpl	%1,%%a0\n\t"
		"blt	2b\n\t"
		"addql	#1,%%d0\n\t"
		"cmpil	%2,%%d0\n\t"
		"bne	1b\n\t"
		: /* No output */
		: "i" (CACHE_LINE_SIZE),
		  "i" (DCACHE_SIZE / CACHE_WAYS),
		  "i" (CACHE_WAYS)
		: "d0", "a0" );
}

/***************************************************************************/
#endif /* CACHE_PUSH */
/***************************************************************************/
