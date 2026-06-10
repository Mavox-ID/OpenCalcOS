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

void *memset(void *s, int c, size_t count)
{
	void *xs = s;
	size_t temp;

	if (!count)
		return xs;
	c &= 0xff;
	c |= c << 8;
	c |= c << 16;
	if ((long)s & 1) {
		char *cs = s;
		*cs++ = c;
		s = cs;
		count--;
	}
	if (count > 2 && (long)s & 2) {
		short *ss = s;
		*ss++ = c;
		s = ss;
		count -= 2;
	}
	temp = count >> 2;
	if (temp) {
		long *ls = s;
#if defined(CONFIG_M68000) || defined(CONFIG_COLDFIRE)
		for (; temp; temp--)
			*ls++ = c;
#else
		size_t temp1;
		asm volatile (
			"	movel %1,%2\n"
			"	andw  #7,%2\n"
			"	lsrl  #3,%1\n"
			"	negw  %2\n"
			"	jmp   %%pc@(2f,%2:w:2)\n"
			"1:	movel %3,%0@+\n"
			"	movel %3,%0@+\n"
			"	movel %3,%0@+\n"
			"	movel %3,%0@+\n"
			"	movel %3,%0@+\n"
			"	movel %3,%0@+\n"
			"	movel %3,%0@+\n"
			"	movel %3,%0@+\n"
			"2:	dbra  %1,1b\n"
			"	clrw  %1\n"
			"	subql #1,%1\n"
			"	jpl   1b"
			: "=a" (ls), "=d" (temp), "=&d" (temp1)
			: "d" (c), "0" (ls), "1" (temp));
#endif
		s = ls;
	}
	if (count & 2) {
		short *ss = s;
		*ss++ = c;
		s = ss;
	}
	if (count & 1) {
		char *cs = s;
		*cs = c;
	}
	return xs;
}
EXPORT_SYMBOL(memset);
