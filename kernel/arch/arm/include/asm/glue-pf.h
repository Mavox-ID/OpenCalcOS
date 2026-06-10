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
#ifndef ASM_GLUE_PF_H
#define ASM_GLUE_PF_H

#include <asm/glue.h>

/*
 *	Prefetch Abort Model
 *	================
 *
 *	We have the following to choose from:
 *	  legacy	- no IFSR, no IFAR
 *	  v6		- ARMv6: IFSR, no IFAR
 *	  v7		- ARMv7: IFSR and IFAR
 */

#undef CPU_PABORT_HANDLER
#undef MULTI_PABORT

#ifdef CONFIG_CPU_PABRT_LEGACY
# ifdef CPU_PABORT_HANDLER
#  define MULTI_PABORT 1
# else
#  define CPU_PABORT_HANDLER legacy_pabort
# endif
#endif

#ifdef CONFIG_CPU_PABRT_V6
# ifdef CPU_PABORT_HANDLER
#  define MULTI_PABORT 1
# else
#  define CPU_PABORT_HANDLER v6_pabort
# endif
#endif

#ifdef CONFIG_CPU_PABRT_V7
# ifdef CPU_PABORT_HANDLER
#  define MULTI_PABORT 1
# else
#  define CPU_PABORT_HANDLER v7_pabort
# endif
#endif

#ifndef CPU_PABORT_HANDLER
#error Unknown prefetch abort handler type
#endif

#endif
