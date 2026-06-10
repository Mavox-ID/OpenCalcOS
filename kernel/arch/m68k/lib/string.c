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
#define __IN_STRING_C

#include <beep/module.h>
#include <beep/string.h>

char *strcpy(char *dest, const char *src)
{
	return __kernel_strcpy(dest, src);
}
EXPORT_SYMBOL(strcpy);

char *strcat(char *dest, const char *src)
{
	return __kernel_strcpy(dest + __kernel_strlen(dest), src);
}
EXPORT_SYMBOL(strcat);
