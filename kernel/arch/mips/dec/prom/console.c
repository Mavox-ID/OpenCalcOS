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
#include <beep/console.h>
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/string.h>

#include <asm/dec/prom.h>

static void __init prom_console_write(struct console *con, const char *s,
				      unsigned int c)
{
	char buf[81];
	unsigned int chunk = sizeof(buf) - 1;

	while (c > 0) {
		if (chunk > c)
			chunk = c;
		memcpy(buf, s, chunk);
		buf[chunk] = '\0';
		prom_printf("%s", buf);
		s += chunk;
		c -= chunk;
	}
}

static struct console promcons __initdata = {
	.name	= "prom",
	.write	= prom_console_write,
	.flags	= CON_BOOT | CON_PRINTBUFFER,
	.index	= -1,
};

void __init register_prom_console(void)
{
	register_console(&promcons);
}
