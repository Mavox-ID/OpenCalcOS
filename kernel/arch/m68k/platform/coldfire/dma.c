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
/*
 *	dma.c -- Freescale ColdFire DMA support
 *
 *	Copyright (C) 2007, Greg Ungerer (gerg@snapgear.com)
 */

/***************************************************************************/

#include <beep/kernel.h>
#include <beep/module.h>
#include <asm/dma.h>
#include <asm/coldfire.h>
#include <asm/mcfsim.h>
#include <asm/mcfdma.h>

/***************************************************************************/

/*
 *      DMA channel base address table.
 */
unsigned int dma_base_addr[MAX_M68K_DMA_CHANNELS] = {
#ifdef MCFDMA_BASE0
	MCFDMA_BASE0,
#endif
#ifdef MCFDMA_BASE1
	MCFDMA_BASE1,
#endif
#ifdef MCFDMA_BASE2
	MCFDMA_BASE2,
#endif
#ifdef MCFDMA_BASE3
	MCFDMA_BASE3,
#endif
};
EXPORT_SYMBOL(dma_base_addr);

unsigned int dma_device_address[MAX_M68K_DMA_CHANNELS];
EXPORT_SYMBOL(dma_device_address);

/***************************************************************************/
