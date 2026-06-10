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
#ifndef ATOM_TYPES_H
#define ATOM_TYPES_H

/* sync atom types to kernel types */

typedef uint16_t USHORT;
typedef uint32_t ULONG;
typedef uint8_t UCHAR;


#ifndef ATOM_BIG_ENDIAN
#if defined(__BIG_ENDIAN)
#define ATOM_BIG_ENDIAN 1
#else
#define ATOM_BIG_ENDIAN 0
#endif
#endif
#endif
