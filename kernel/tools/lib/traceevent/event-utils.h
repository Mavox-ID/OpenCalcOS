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
#ifndef __UTIL_H
#define __UTIL_H

#include <ctype.h>

/* Can be overridden */
void die(const char *fmt, ...);
void *malloc_or_die(unsigned int size);
void warning(const char *fmt, ...);
void pr_stat(const char *fmt, ...);
void vpr_stat(const char *fmt, va_list ap);

/* Always available */
void __die(const char *fmt, ...);
void __warning(const char *fmt, ...);
void __pr_stat(const char *fmt, ...);

void __vdie(const char *fmt, ...);
void __vwarning(const char *fmt, ...);
void __vpr_stat(const char *fmt, ...);

#define min(x, y) ({				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(void) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; })

static inline char *strim(char *string)
{
	char *ret;

	if (!string)
		return NULL;
	while (*string) {
		if (!isspace(*string))
			break;
		string++;
	}
	ret = string;

	string = ret + strlen(ret) - 1;
	while (string > ret) {
		if (!isspace(*string))
			break;
		string--;
	}
	string[1] = 0;

	return ret;
}

static inline int has_text(const char *text)
{
	if (!text)
		return 0;

	while (*text) {
		if (!isspace(*text))
			return 1;
		text++;
	}

	return 0;
}

#endif
