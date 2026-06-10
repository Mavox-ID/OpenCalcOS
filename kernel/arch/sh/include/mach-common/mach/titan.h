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
#ifndef _ASM_SH_TITAN_H
#define _ASM_SH_TITAN_H

#include <beep/sh_intc.h>

#define __IO_PREFIX titan
#include <asm/io_generic.h>

/* IRQ assignments */
#define TITAN_IRQ_WAN		evt2irq(0x240)	/* eth0 (WAN) */
#define TITAN_IRQ_LAN		evt2irq(0x2a0)	/* eth1 (LAN) */
#define TITAN_IRQ_MPCIA		evt2irq(0x300)	/* mPCI A */
#define TITAN_IRQ_MPCIB		evt2irq(0x360)	/* mPCI B */
#define TITAN_IRQ_USB		evt2irq(0x360)	/* USB */

#endif /* __ASM_SH_TITAN_H */
