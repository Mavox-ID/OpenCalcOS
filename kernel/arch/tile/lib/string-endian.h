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
#include <asm/byteorder.h>

#ifdef __LITTLE_ENDIAN
#define MASK(x) (__insn_shl(1ULL, (x << 3)) - 1)
#define NULMASK(x) ((2ULL << x) - 1)
#define CFZ(x) __insn_ctz(x)
#define REVCZ(x) __insn_clz(x)
#else
#define MASK(x) (__insn_shl(-2LL, ((-x << 3) - 1)))
#define NULMASK(x) (-2LL << (63 - x))
#define CFZ(x) __insn_clz(x)
#define REVCZ(x) __insn_ctz(x)
#endif
