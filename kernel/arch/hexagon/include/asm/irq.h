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
#ifndef _ASM_IRQ_H_
#define _ASM_IRQ_H_

/* Number of first-level interrupts associated with the CPU core. */
#define HEXAGON_CPUINTS 32

/*
 * Must define NR_IRQS before including <asm-generic/irq.h>
 * 64 == the two SIRC's, 176 == the two gpio's
 *
 * IRQ configuration is still in flux; defining this to a comfortably
 * large number.
 */
#define NR_IRQS 512

#include <asm-generic/irq.h>

#endif
