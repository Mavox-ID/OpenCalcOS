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
#ifndef __VICTOR_MPC30X_H
#define __VICTOR_MPC30X_H

#include <asm/vr41xx/irq.h>

/*
 * General-Purpose I/O Pin Number
 */
#define VRC4173_PIN			1
#define MQ200_PIN			4

/*
 * Interrupt Number
 */
#define VRC4173_CASCADE_IRQ		GIU_IRQ(VRC4173_PIN)
#define MQ200_IRQ			GIU_IRQ(MQ200_PIN)

#endif /* __VICTOR_MPC30X_H */
