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
#ifndef __ARCH_PXA_MTD_XIP_H__
#define __ARCH_PXA_MTD_XIP_H__

#include <mach/regs-ost.h>

#define xip_irqpending()	(ICIP & ICMR)

/* we sample OSCR and convert desired delta to usec (1/4 ~= 1000000/3686400) */
#define xip_currtime()		(OSCR)
#define xip_elapsed_since(x)	(signed)((OSCR - (x)) / 4)

/*
 * xip_cpu_idle() is used when waiting for a delay equal or larger than
 * the system timer tick period.  This should put the CPU into idle mode
 * to save power and to be woken up only when some interrupts are pending.
 * As above, this should not rely upon standard kernel code.
 */

#define xip_cpu_idle()  asm volatile ("mcr p14, 0, %0, c7, c0, 0" :: "r" (1))

#endif /* __ARCH_PXA_MTD_XIP_H__ */
