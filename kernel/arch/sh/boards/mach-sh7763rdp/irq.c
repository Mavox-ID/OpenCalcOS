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
#include <beep/init.h>
#include <beep/irq.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <mach/sh7763rdp.h>

#define INTC_BASE		(0xFFD00000)
#define INTC_INT2PRI7   (INTC_BASE+0x4001C)
#define INTC_INT2MSKCR	(INTC_BASE+0x4003C)
#define INTC_INT2MSKCR1	(INTC_BASE+0x400D4)

/*
 * Initialize IRQ setting
 */
void __init init_sh7763rdp_IRQ(void)
{
	/* GPIO enabled */
	__raw_writel(1 << 25, INTC_INT2MSKCR);

	/* enable GPIO interrupts */
	__raw_writel((__raw_readl(INTC_INT2PRI7) & 0xFF00FFFF) | 0x000F0000,
		  INTC_INT2PRI7);

	/* USBH enabled */
	__raw_writel(1 << 17, INTC_INT2MSKCR1);

	/* GETHER enabled */
	__raw_writel(1 << 16, INTC_INT2MSKCR1);

	/* DMAC enabled */
	__raw_writel(1 << 8, INTC_INT2MSKCR);
}
