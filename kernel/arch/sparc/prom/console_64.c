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
#include <beep/kernel.h>
#include <beep/sched.h>
#include <asm/openprom.h>
#include <asm/oplib.h>
#include <beep/string.h>

static int __prom_console_write_buf(const char *buf, int len)
{
	unsigned long args[7];
	int ret;

	args[0] = (unsigned long) "write";
	args[1] = 3;
	args[2] = 1;
	args[3] = (unsigned int) prom_stdout;
	args[4] = (unsigned long) buf;
	args[5] = (unsigned int) len;
	args[6] = (unsigned long) -1;

	p1275_cmd_direct(args);

	ret = (int) args[6];
	if (ret < 0)
		return -1;
	return ret;
}

void prom_console_write_buf(const char *buf, int len)
{
	while (len) {
		int n = __prom_console_write_buf(buf, len);
		if (n < 0)
			continue;
		len -= n;
		buf += len;
	}
}
