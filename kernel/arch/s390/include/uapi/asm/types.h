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
#ifndef _UAPI_S390_TYPES_H
#define _UAPI_S390_TYPES_H

#include <asm-generic/int-ll64.h>

#ifndef __ASSEMBLY__

/* A address type so that arithmetic can be done on it & it can be upgraded to
   64 bit when necessary 
*/
typedef unsigned long addr_t; 
typedef __signed__ long saddr_t;

#endif /* __ASSEMBLY__ */

#endif /* _UAPI_S390_TYPES_H */
