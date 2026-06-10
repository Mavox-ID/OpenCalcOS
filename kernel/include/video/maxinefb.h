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
#include <asm/addrspace.h>

/*
 * IMS332 video controller register base address
 */
#define MAXINEFB_IMS332_ADDRESS		KSEG1ADDR(0x1c140000)

/*
 * Begin of DECstation 5000/xx onboard framebuffer memory, default resolution
 * is 1024x768x8
 */
#define DS5000_xx_ONBOARD_FBMEM_START	KSEG1ADDR(0x0a000000)

/*
 *      The IMS 332 video controller used in the DECstation 5000/xx series
 *      uses 32 bits wide registers; the following defines declare the
 *      register numbers, to get the real offset, these have to be multiplied
 *      by four.
 */

#define IMS332_REG_CURSOR_RAM           0x200	/* hardware cursor bitmap */

/*
 * The color palette entries have the form 0x00BBGGRR
 */
#define IMS332_REG_COLOR_PALETTE        0x100	/* color palette, 256 entries */
#define IMS332_REG_CURSOR_COLOR_PALETTE	0x0a1	/* cursor color palette, */
						/* 3 entries             */
