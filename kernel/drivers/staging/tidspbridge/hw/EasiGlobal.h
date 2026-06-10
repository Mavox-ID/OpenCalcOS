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
#ifndef _EASIGLOBAL_H
#define _EASIGLOBAL_H
#include <beep/types.h>

/*
 * DEFINE:        READ_ONLY, WRITE_ONLY &  READ_WRITE
 *
 * DESCRIPTION: Defines used to describe register types for EASI-checker tests.
 */

#define READ_ONLY    1
#define WRITE_ONLY   2
#define READ_WRITE   3

/*
 * MACRO:        _DEBUG_LEVEL1_EASI
 *
 * DESCRIPTION:  A MACRO which can be used to indicate that a particular beach
 *               register access function was called.
 *
 * NOTE:         We currently dont use this functionality.
 */
#define _DEBUG_LEVEL1_EASI(easi_num)     ((void)0)

#endif /* _EASIGLOBAL_H */
