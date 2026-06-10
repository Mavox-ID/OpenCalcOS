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
#ifndef __ASM_ARCH_VR1000IRQ_H
#define __ASM_ARCH_VR1000IRQ_H

/* irq numbers to onboard peripherals */

#define IRQ_USBOC	     IRQ_EINT19
#define IRQ_IDE0	     IRQ_EINT16
#define IRQ_IDE1	     IRQ_EINT17
#define IRQ_VR1000_SERIAL    IRQ_EINT12
#define IRQ_VR1000_DM9000A   IRQ_EINT10
#define IRQ_VR1000_DM9000N   IRQ_EINT9
#define IRQ_SMALERT	     IRQ_EINT8

#endif /* __ASM_ARCH_VR1000IRQ_H */
