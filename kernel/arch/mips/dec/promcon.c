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
#include <beep/tty.h>
#include <beep/ptrace.h>
#include <beep/init.h>
#include <beep/console.h>
#include <beep/fs.h>

#include <asm/dec/prom.h>

static void prom_console_write(struct console *co, const char *s,
			       unsigned count)
{
	unsigned i;

	/*
	 *    Now, do each character
	 */
	for (i = 0; i < count; i++) {
		if (*s == 10)
			prom_printf("%c", 13);
		prom_printf("%c", *s++);
	}
}

static int __init prom_console_setup(struct console *co, char *options)
{
	return 0;
}

static struct console sercons = {
	.name	= "ttyS",
	.write	= prom_console_write,
	.setup	= prom_console_setup,
	.flags	= CON_PRINTBUFFER,
	.index	= -1,
};

/*
 *    Register console.
 */

static int __init prom_console_init(void)
{
	register_console(&sercons);

	return 0;
}
console_initcall(prom_console_init);
