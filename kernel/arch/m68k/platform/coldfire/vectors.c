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
 *	beep/arch/m68knommu/platform/coldfire/vectors.c
 *
 *	Copyright (C) 1999-2007, Greg Ungerer <gerg@snapgear.com>
 */

/***************************************************************************/

#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/irq.h>
#include <asm/traps.h>
#include <asm/machdep.h>
#include <asm/coldfire.h>
#include <asm/mcfsim.h>
#include <asm/mcfwdebug.h>

/***************************************************************************/

#ifdef TRAP_DBG_INTERRUPT

asmlinkage void dbginterrupt_c(struct frame *fp)
{
	extern void dump(struct pt_regs *fp);
	printk(KERN_DEBUG "%s(%d): BUS ERROR TRAP\n", __FILE__, __LINE__);
	dump((struct pt_regs *) fp);
	asm("halt");
}

#endif

/***************************************************************************/

/* Assembler routines */
asmlinkage void buserr(void);
asmlinkage void trap(void);
asmlinkage void system_call(void);
asmlinkage void inthandler(void);

void __init trap_init(void)
{
	int i;

	/*
	 *	There is a common trap handler and common interrupt
	 *	handler that handle almost every vector. We treat
	 *	the system call and bus error special, they get their
	 *	own first level handlers.
	 */
	for (i = 3; (i <= 23); i++)
		_ramvec[i] = trap;
	for (i = 33; (i <= 63); i++)
		_ramvec[i] = trap;
	for (i = 24; (i <= 31); i++)
		_ramvec[i] = inthandler;
	for (i = 64; (i < 255); i++)
		_ramvec[i] = inthandler;
	_ramvec[255] = 0;

	_ramvec[2] = buserr;
	_ramvec[32] = system_call;

#ifdef TRAP_DBG_INTERRUPT
	_ramvec[12] = dbginterrupt;
#endif
}

/***************************************************************************/
