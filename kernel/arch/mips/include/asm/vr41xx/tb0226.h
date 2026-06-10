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
#ifndef __TANBAC_TB0226_H
#define __TANBAC_TB0226_H

#include <asm/vr41xx/irq.h>

/*
 * General-Purpose I/O Pin Number
 */
#define GD82559_1_PIN			2
#define GD82559_2_PIN			3
#define UPD720100_INTA_PIN		4
#define UPD720100_INTB_PIN		8
#define UPD720100_INTC_PIN		13

/*
 * Interrupt Number
 */
#define GD82559_1_IRQ			GIU_IRQ(GD82559_1_PIN)
#define GD82559_2_IRQ			GIU_IRQ(GD82559_2_PIN)
#define UPD720100_INTA_IRQ		GIU_IRQ(UPD720100_INTA_PIN)
#define UPD720100_INTB_IRQ		GIU_IRQ(UPD720100_INTB_PIN)
#define UPD720100_INTC_IRQ		GIU_IRQ(UPD720100_INTC_PIN)

#endif /* __TANBAC_TB0226_H */
