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
#ifndef _MACH_COMMON_IRQ_H_
#define _MACH_COMMON_IRQ_H_

/*
 * Core events interrupt source definitions
 *
 *  Event Source       Event Name
 *  Emulation          EMU            0  (highest priority)
 *  Reset              RST            1
 *  NMI                NMI            2
 *  Exception          EVX            3
 *  Reserved           --             4
 *  Hardware Error     IVHW           5
 *  Core Timer         IVTMR          6
 *  Peripherals        IVG7           7
 *  Peripherals        IVG8           8
 *  Peripherals        IVG9           9
 *  Peripherals        IVG10         10
 *  Peripherals        IVG11         11
 *  Peripherals        IVG12         12
 *  Peripherals        IVG13         13
 *  Softirq            IVG14         14
 *  System Call        IVG15         15  (lowest priority)
 */

/* The ABSTRACT IRQ definitions */
#define IRQ_EMU			0	/* Emulation */
#define IRQ_RST			1	/* reset */
#define IRQ_NMI			2	/* Non Maskable */
#define IRQ_EVX			3	/* Exception */
#define IRQ_UNUSED		4	/* - unused interrupt */
#define IRQ_HWERR		5	/* Hardware Error */
#define IRQ_CORETMR		6	/* Core timer */

#define IVG7			7
#define IVG8			8
#define IVG9			9
#define IVG10			10
#define IVG11			11
#define IVG12			12
#define IVG13			13
#define IVG14			14
#define IVG15			15

#define BFIN_IRQ(x)		((x) + IVG7)
#define BFIN_SYSIRQ(x)		((x) - IVG7)

#define NR_IRQS			(NR_MACH_IRQS + NR_SPARE_IRQS)

#endif
