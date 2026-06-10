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
#ifndef _ASM_IA64_SN_TYPES_H
#define _ASM_IA64_SN_TYPES_H

#include <beep/types.h>

typedef unsigned long 	cpuid_t;
typedef signed short	nasid_t;	/* node id in numa-as-id space */
typedef signed char	partid_t;	/* partition ID type */
typedef unsigned int    moduleid_t;     /* user-visible module number type */
typedef unsigned int    cmoduleid_t;    /* kernel compact module id type */
typedef unsigned char	slotid_t;	/* slot (blade) within module */
typedef unsigned char	slabid_t;	/* slab (asic) within slot */
typedef u64 nic_t;
typedef unsigned long iopaddr_t;
typedef unsigned long paddr_t;
typedef short cnodeid_t;

#endif /* _ASM_IA64_SN_TYPES_H */
