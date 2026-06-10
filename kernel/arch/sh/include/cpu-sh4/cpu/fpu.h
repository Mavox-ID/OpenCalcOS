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
#ifndef __CPU_SH4_FPU_H
#define __CPU_SH4_FPU_H

#define FPSCR_ENABLE_MASK	0x00000f80UL

#define FPSCR_FMOV_DOUBLE	(1<<1)

#define FPSCR_CAUSE_INEXACT	(1<<12)
#define FPSCR_CAUSE_UNDERFLOW	(1<<13)
#define FPSCR_CAUSE_OVERFLOW	(1<<14)
#define FPSCR_CAUSE_DIVZERO	(1<<15)
#define FPSCR_CAUSE_INVALID	(1<<16)
#define FPSCR_CAUSE_ERROR 	(1<<17)

#define FPSCR_DBL_PRECISION	(1<<19)
#define FPSCR_ROUNDING_MODE(x)	((x >> 20) & 3)
#define FPSCR_RM_NEAREST	(0)
#define FPSCR_RM_ZERO		(1)

#endif
