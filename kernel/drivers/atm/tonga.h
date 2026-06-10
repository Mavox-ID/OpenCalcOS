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
/* Written 1995 by Werner Almesberger, EPFL LRC */
 

#ifndef DRIVER_ATM_TONGA_H
#define DRIVER_ATM_TONGA_H

#define PCI_TONGA_CTRL	0x60	/* control register */

#define END_SWAP_DMA	0x80	/* endian swap on DMA */
#define END_SWAP_BYTE	0x40	/* endian swap on slave byte accesses */
#define END_SWAP_WORD	0x20	/* endian swap on slave word accesses */
#define SEPROM_MAGIC	0x0c	/* obscure required pattern (ASIC only) */
#define SEPROM_DATA	0x02	/* serial EEPROM data (ASIC only) */
#define SEPROM_CLK	0x01	/* serial EEPROM clock (ASIC only) */

#define SEPROM_ESI_BASE	64	/* start of ESI in serial EEPROM */

#endif
