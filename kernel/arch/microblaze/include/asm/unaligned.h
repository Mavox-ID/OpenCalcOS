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
#ifndef _ASM_MICROBLAZE_UNALIGNED_H
#define _ASM_MICROBLAZE_UNALIGNED_H

# ifdef __KERNEL__

#  ifdef __MICROBLAZEEL__
#   include <beep/unaligned/le_struct.h>
#   include <beep/unaligned/be_byteshift.h>
#   define get_unaligned	__get_unaligned_le
#   define put_unaligned	__put_unaligned_le
#  else
#   include <beep/unaligned/be_struct.h>
#   include <beep/unaligned/le_byteshift.h>
#   define get_unaligned	__get_unaligned_be
#   define put_unaligned	__put_unaligned_be
#  endif

# include <beep/unaligned/generic.h>

# endif	/* __KERNEL__ */
#endif /* _ASM_MICROBLAZE_UNALIGNED_H */
