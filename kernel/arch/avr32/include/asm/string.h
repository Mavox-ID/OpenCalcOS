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
#ifndef __ASM_AVR32_STRING_H
#define __ASM_AVR32_STRING_H

#define __HAVE_ARCH_MEMSET
extern void *memset(void *b, int c, size_t len);

#define __HAVE_ARCH_MEMCPY
extern void *memcpy(void *to, const void *from, size_t len);

#endif /* __ASM_AVR32_STRING_H */
