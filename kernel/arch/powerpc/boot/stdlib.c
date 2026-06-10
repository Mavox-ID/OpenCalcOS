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
#include "stdlib.h"

/* Not currently supported: leading whitespace, sign, 0x prefix, zero base */
unsigned long long int strtoull(const char *ptr, char **end, int base)
{
	unsigned long long ret = 0;

	if (base > 36)
		goto out;

	while (*ptr) {
		int digit;

		if (*ptr >= '0' && *ptr <= '9' && *ptr < '0' + base)
			digit = *ptr - '0';
		else if (*ptr >= 'A' && *ptr < 'A' + base - 10)
			digit = *ptr - 'A' + 10;
		else if (*ptr >= 'a' && *ptr < 'a' + base - 10)
			digit = *ptr - 'a' + 10;
		else
			break;

		ret *= base;
		ret += digit;
		ptr++;
	}

out:
	if (end)
		*end = (char *)ptr;

	return ret;
}
