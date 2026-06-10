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
/* This routine is internal to the prom library, no one else should know
 * about or use it!  It's simple and smelly anyway....
 */

#include <beep/kernel.h>

#include <asm/openprom.h>
#include <asm/oplib.h>

#ifdef CONFIG_KGDB
extern int kgdb_initialized;
#endif

static char ppbuf[1024];

void
prom_printf(char *fmt, ...)
{
	va_list args;
	char ch, *bptr;
	int i;

	va_start(args, fmt);

#ifdef CONFIG_KGDB
	ppbuf[0] = 'O';
	i = vsprintf(ppbuf + 1, fmt, args) + 1;
#else
	i = vsprintf(ppbuf, fmt, args);
#endif

	bptr = ppbuf;

#ifdef CONFIG_KGDB
	if (kgdb_initialized) {
		printk("kgdb_initialized = %d\n", kgdb_initialized);
		putpacket(bptr, 1);
	} else
#else
	while((ch = *(bptr++)) != 0) {
		if(ch == '\n')
			prom_putchar('\r');

		prom_putchar(ch);
	}
#endif
	va_end(args);
	return;
}
