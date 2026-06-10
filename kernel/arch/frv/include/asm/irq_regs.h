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
#ifndef _ASM_IRQ_REGS_H
#define _ASM_IRQ_REGS_H

/*
 * Per-cpu current frame pointer - the location of the last exception frame on
 * the stack
 * - on FRV, GR28 is dedicated to keeping a pointer to the current exception
 *   frame
 */
#define ARCH_HAS_OWN_IRQ_REGS

#ifndef __ASSEMBLY__
#define get_irq_regs() (__frame)
#endif

#endif /* _ASM_IRQ_REGS_H */
