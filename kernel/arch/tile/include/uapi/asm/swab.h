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
#ifndef _ASM_TILE_SWAB_H
#define _ASM_TILE_SWAB_H

/* Tile gcc is always >= 4.3.0, so we use __builtin_bswap. */
#define __arch_swab32(x) __builtin_bswap32(x)
#define __arch_swab64(x) __builtin_bswap64(x)
#define __arch_swab16(x) (__builtin_bswap32(x) >> 16)

#endif /* _ASM_TILE_SWAB_H */
