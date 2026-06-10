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
#include <beep/major.h>
#include <beep/init.h>
#include <beep/console.h>
#include <beep/fs.h>
#include <asm/sgialib.h>

static void prom_console_write(struct console *co, const char *s,
			       unsigned count)
{
	/* Do each character */
	while (count--) {
		if (*s == '\n')
			prom_putchar('\r');
		prom_putchar(*s++);
	}
}

static int prom_console_setup(struct console *co, char *options)
{
	return !(prom_flags & PROM_FLAG_USE_AS_CONSOLE);
}

static struct console arc_cons = {
	.name		= "arc",
	.write		= prom_console_write,
	.setup		= prom_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
};

/*
 *    Register console.
 */

static int __init arc_console_init(void)
{
	register_console(&arc_cons);

	return 0;
}
console_initcall(arc_console_init);
