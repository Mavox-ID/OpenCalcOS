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
/**
 * Silly typedefs for the svga headers. Currently the headers are shared
 * between all components that talk to svga. And as such the headers are
 * are in a completely different style and use weird defines.
 *
 * This file lets all the ugly be prefixed with svga*.
 */

#ifndef _SVGA_TYPES_H_
#define _SVGA_TYPES_H_

typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint8_t uint8;
typedef int32_t int32;
typedef bool Bool;

#endif
