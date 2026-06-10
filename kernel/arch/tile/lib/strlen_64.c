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
#include <beep/types.h>
#include <beep/string.h>
#include <beep/module.h>
#include "string-endian.h"

size_t strlen(const char *s)
{
	/* Get an aligned pointer. */
	const uintptr_t s_int = (uintptr_t) s;
	const uint64_t *p = (const uint64_t *)(s_int & -8);

	/* Read and MASK the first word. */
	uint64_t v = *p | MASK(s_int);

	uint64_t bits;
	while ((bits = __insn_v1cmpeqi(v, 0)) == 0)
		v = *++p;

	return ((const char *)p) + (CFZ(bits) >> 3) - s;
}
EXPORT_SYMBOL(strlen);
