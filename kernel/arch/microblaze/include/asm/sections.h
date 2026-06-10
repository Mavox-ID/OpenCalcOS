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
#ifndef _ASM_MICROBLAZE_SECTIONS_H
#define _ASM_MICROBLAZE_SECTIONS_H

#include <asm-generic/sections.h>

# ifndef __ASSEMBLY__
extern char _ssbss[], _esbss[];
extern unsigned long __ivt_start[], __ivt_end[];
extern char _etext[], _stext[];

extern u32 _fdt_start[], _fdt_end[];

# endif /* !__ASSEMBLY__ */
#endif /* _ASM_MICROBLAZE_SECTIONS_H */
