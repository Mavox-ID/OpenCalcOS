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
#ifndef _ASM_MICROBLAZE_MODULE_H
#define _ASM_MICROBLAZE_MODULE_H

#include <asm-generic/module.h>

/* Microblaze Relocations */
#define R_MICROBLAZE_NONE 0
#define R_MICROBLAZE_32 1
#define R_MICROBLAZE_32_PCREL 2
#define R_MICROBLAZE_64_PCREL 3
#define R_MICROBLAZE_32_PCREL_LO 4
#define R_MICROBLAZE_64 5
#define R_MICROBLAZE_32_LO 6
#define R_MICROBLAZE_SRO32 7
#define R_MICROBLAZE_SRW32 8
#define R_MICROBLAZE_64_NONE 9
#define R_MICROBLAZE_32_SYM_OP_SYM 10
/* Keep this the last entry. */
#define R_MICROBLAZE_NUM 11

typedef struct { volatile int counter; } module_t;

#endif /* _ASM_MICROBLAZE_MODULE_H */
