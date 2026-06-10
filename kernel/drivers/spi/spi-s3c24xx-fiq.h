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
/* We have R8 through R13 to play with */

#ifdef __ASSEMBLY__
#define __REG_NR(x)     r##x
#else
#define __REG_NR(x)     (x)
#endif

#define fiq_rspi	__REG_NR(8)
#define fiq_rtmp	__REG_NR(9)
#define fiq_rrx		__REG_NR(10)
#define fiq_rtx		__REG_NR(11)
#define fiq_rcount	__REG_NR(12)
#define fiq_rirq	__REG_NR(13)
