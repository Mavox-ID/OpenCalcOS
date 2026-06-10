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
#ifndef _ASM_MIPS_BOARDS_SIM_H
#define _ASM_MIPS_BOARDS_SIM_H

#define STATS_ON        1
#define STATS_OFF       2
#define STATS_CLEAR     3
#define STATS_DUMP      4
#define TRACE_ON		5
#define TRACE_OFF       6


#define simcfg(code)						\
({					   \
	__asm__  __volatile__( \
        "sltiu $0,$0, %0" \
		::"i"(code)					\
		); \
})



#endif
