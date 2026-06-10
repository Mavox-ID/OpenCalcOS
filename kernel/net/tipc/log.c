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
#include "core.h"
#include "config.h"

/**
 * tipc_snprintf - append formatted output to print buffer
 * @buf: pointer to print buffer
 * @len: buffer length
 * @fmt: formatted info to be printed
 */
int tipc_snprintf(char *buf, int len, const char *fmt, ...)
{
	int i;
	va_list args;

	va_start(args, fmt);
	i = vscnprintf(buf, len, fmt, args);
	va_end(args);
	return i;
}
