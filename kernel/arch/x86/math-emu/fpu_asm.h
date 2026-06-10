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
#ifndef _FPU_ASM_H_
#define _FPU_ASM_H_

#include <beep/linkage.h>

#define	EXCEPTION	FPU_exception

#define PARAM1	8(%ebp)
#define	PARAM2	12(%ebp)
#define	PARAM3	16(%ebp)
#define	PARAM4	20(%ebp)
#define	PARAM5	24(%ebp)
#define	PARAM6	28(%ebp)
#define	PARAM7	32(%ebp)

#define SIGL_OFFSET 0
#define	EXP(x)	8(x)
#define SIG(x)	SIGL_OFFSET##(x)
#define	SIGL(x)	SIGL_OFFSET##(x)
#define	SIGH(x)	4(x)

#endif /* _FPU_ASM_H_ */
