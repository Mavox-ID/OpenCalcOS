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
#ifndef MPI2_TYPE_H
#define MPI2_TYPE_H


/*******************************************************************************
 * Define MPI2_POINTER if it hasn't already been defined. By default
 * MPI2_POINTER is defined to be a near pointer. MPI2_POINTER can be defined as
 * a far pointer by defining MPI2_POINTER as "far *" before this header file is
 * included.
 */
#ifndef MPI2_POINTER
#define MPI2_POINTER     *
#endif

/* the basic types may have already been included by mpi_type.h */
#ifndef MPI_TYPE_H
/*****************************************************************************
*
*               Basic Types
*
*****************************************************************************/

typedef u8 U8;
typedef __le16 U16;
typedef __le32 U32;
typedef __le64 U64 __attribute__((aligned(4)));

/*****************************************************************************
*
*               Pointer Types
*
*****************************************************************************/

typedef U8      *PU8;
typedef U16     *PU16;
typedef U32     *PU32;
typedef U64     *PU64;

#endif

#endif

