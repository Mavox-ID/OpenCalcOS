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
#ifndef _XTENSA_XT2000_SERIAL_H
#define _XTENSA_XT2000_SERIAL_H

#include <variant/core.h>
#include <asm/io.h>

/*  National-Semi PC16552D DUART:  */

#define DUART16552_1_INTNUM	XCHAL_EXTINT4_NUM
#define DUART16552_2_INTNUM	XCHAL_EXTINT5_NUM

#define DUART16552_1_ADDR	IOADDR(0x0d050020)	/* channel 1 */
#define DUART16552_2_ADDR	IOADDR(0x0d050000)	/* channel 2 */

#define DUART16552_XTAL_FREQ	18432000	/* crystal frequency in Hz */
#define BASE_BAUD ( DUART16552_XTAL_FREQ / 16 )

#endif /* _XTENSA_XT2000_SERIAL_H */
