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
#ifndef __ASM_ARCH_SERIAL_H
#define __ASM_ARCH_SERIAL_H

#include <beep/init.h>

/*
 * Memory entry used for the DEBUG_LL UART configuration, relative to
 * start of RAM. See also uncompress.h and debug-macro.S.
 *
 * Note that using a memory location for storing the UART configuration
 * has at least two limitations:
 *
 * 1. Kernel uncompress code cannot overlap OMAP_UART_INFO as the
 *    uncompress code could then partially overwrite itself
 * 2. We assume printascii is called at least once before paging_init,
 *    and addruart has a chance to read OMAP_UART_INFO
 */
#define OMAP_UART_INFO_OFS	0x3ffc

/* OMAP1 serial ports */
#define OMAP1_UART1_BASE	0xfffb0000
#define OMAP1_UART2_BASE	0xfffb0800
#define OMAP1_UART3_BASE	0xfffb9800

#define OMAP_PORT_SHIFT		2
#define OMAP7XX_PORT_SHIFT	0

#define OMAP1510_BASE_BAUD	(12000000/16)
#define OMAP16XX_BASE_BAUD	(48000000/16)

/*
 * DEBUG_LL port encoding stored into the UART1 scratchpad register by
 * decomp_setup in uncompress.h
 */
#define OMAP1UART1		11
#define OMAP1UART2		12
#define OMAP1UART3		13

#ifndef __ASSEMBLER__
extern void omap_serial_init(void);
#endif

#endif
