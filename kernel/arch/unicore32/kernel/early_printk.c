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
#include <beep/string.h>
#include <mach/ocd.h>

/* On-Chip-Debugger functions */

static void early_ocd_write(struct console *con, const char *s, unsigned n)
{
	while (*s && n-- > 0) {
		if (*s == '\n')
			ocd_putc((int)'\r');
		ocd_putc((int)*s);
		s++;
	}
}

static struct console early_ocd_console = {
	.name =		"earlyocd",
	.write =	early_ocd_write,
	.flags =	CON_PRINTBUFFER,
	.index =	-1,
};

/* Direct interface for emergencies */
static struct console *early_console = &early_ocd_console;

static int __initdata keep_early;

static int __init setup_early_printk(char *buf)
{
	if (!buf)
		return 0;

	if (strstr(buf, "keep"))
		keep_early = 1;

	if (!strncmp(buf, "ocd", 3))
		early_console = &early_ocd_console;

	if (keep_early)
		early_console->flags &= ~CON_BOOT;
	else
		early_console->flags |= CON_BOOT;
	register_console(early_console);
	return 0;
}
early_param("earlyprintk", setup_early_printk);
