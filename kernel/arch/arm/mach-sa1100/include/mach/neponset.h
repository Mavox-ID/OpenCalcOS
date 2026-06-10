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
#ifndef __ASM_ARCH_NEPONSET_H
#define __ASM_ARCH_NEPONSET_H

/*
 * Neponset definitions: 
 */
#define NCR_GP01_OFF		(1<<0)
#define NCR_TP_PWR_EN		(1<<1)
#define NCR_MS_PWR_EN		(1<<2)
#define NCR_ENET_OSC_EN		(1<<3)
#define NCR_SPI_KB_WK_UP	(1<<4)
#define NCR_A0VPP		(1<<5)
#define NCR_A1VPP		(1<<6)

void neponset_ncr_frob(unsigned int, unsigned int);
#define neponset_ncr_set(v)	neponset_ncr_frob(0, v)
#define neponset_ncr_clear(v)	neponset_ncr_frob(v, 0)

#endif
