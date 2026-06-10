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
#ifndef _ASM_MICROBLAZE_ELF_H
#define _ASM_MICROBLAZE_ELF_H

#include <uapi/asm/elf.h>

#ifndef __uCbeep__
#ifndef ELF_GREG_T
#endif
#ifndef ELF_NGREG
#endif
#ifndef ELF_GREGSET_T
#endif
#ifndef ELF_FPREGSET_T
#endif
#ifdef __MICROBLAZEEL__
#else
#endif
#define SET_PERSONALITY(ex) \
	set_personality(PER_BEEP_32BIT | (current->personality & (~PER_MASK)))
#endif /* __uCbeep__ */
#endif /* _ASM_MICROBLAZE_ELF_H */
