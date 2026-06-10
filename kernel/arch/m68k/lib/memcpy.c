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
#include <beep/module.h>
#include <beep/string.h>

void *memcpy(void *to, const void *from, size_t n)
{
	void *xto = to;
	size_t temp;

	if (!n)
		return xto;
	if ((long)to & 1) {
		char *cto = to;
		const char *cfrom = from;
		*cto++ = *cfrom++;
		to = cto;
		from = cfrom;
		n--;
	}
#if defined(CONFIG_M68000)
	if ((long)from & 1) {
		char *cto = to;
		const char *cfrom = from;
		for (; n; n--)
			*cto++ = *cfrom++;
		return xto;
	}
#endif
	if (n > 2 && (long)to & 2) {
		short *sto = to;
		const short *sfrom = from;
		*sto++ = *sfrom++;
		to = sto;
		from = sfrom;
		n -= 2;
	}
	temp = n >> 2;
	if (temp) {
		long *lto = to;
		const long *lfrom = from;
#if defined(CONFIG_M68000) || defined(CONFIG_COLDFIRE)
		for (; temp; temp--)
			*lto++ = *lfrom++;
#else
		size_t temp1;
		asm volatile (
			"	movel %2,%3\n"
			"	andw  #7,%3\n"
			"	lsrl  #3,%2\n"
			"	negw  %3\n"
			"	jmp   %%pc@(1f,%3:w:2)\n"
			"4:	movel %0@+,%1@+\n"
			"	movel %0@+,%1@+\n"
			"	movel %0@+,%1@+\n"
			"	movel %0@+,%1@+\n"
			"	movel %0@+,%1@+\n"
			"	movel %0@+,%1@+\n"
			"	movel %0@+,%1@+\n"
			"	movel %0@+,%1@+\n"
			"1:	dbra  %2,4b\n"
			"	clrw  %2\n"
			"	subql #1,%2\n"
			"	jpl   4b"
			: "=a" (lfrom), "=a" (lto), "=d" (temp), "=&d" (temp1)
			: "0" (lfrom), "1" (lto), "2" (temp));
#endif
		to = lto;
		from = lfrom;
	}
	if (n & 2) {
		short *sto = to;
		const short *sfrom = from;
		*sto++ = *sfrom++;
		to = sto;
		from = sfrom;
	}
	if (n & 1) {
		char *cto = to;
		const char *cfrom = from;
		*cto = *cfrom;
	}
	return xto;
}
EXPORT_SYMBOL(memcpy);
