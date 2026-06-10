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
#ifndef SUN3INTS_H
#define SUN3INTS_H

#include <beep/types.h>
#include <beep/interrupt.h>
#include <asm/intersil.h>
#include <asm/oplib.h>
#include <asm/traps.h>
#include <asm/irq.h>

#define SUN3_INT_VECS 192

void sun3_enable_irq(unsigned int irq);
void sun3_disable_irq(unsigned int irq);
extern void sun3_init_IRQ (void);
extern void sun3_enable_interrupts (void);
extern void sun3_disable_interrupts (void);
extern volatile unsigned char* sun3_intreg;

/* master list of VME vectors -- don't fuck with this */
#define SUN3_VEC_FLOPPY		(IRQ_USER+0)
#define SUN3_VEC_VMESCSI0	(IRQ_USER+0)
#define SUN3_VEC_VMESCSI1	(IRQ_USER+1)
#define SUN3_VEC_CG		(IRQ_USER+104)


#endif /* SUN3INTS_H */
