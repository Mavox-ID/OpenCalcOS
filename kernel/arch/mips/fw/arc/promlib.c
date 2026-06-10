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
#include <beep/kernel.h>
#include <asm/sgialib.h>
#include <asm/bcache.h>

/*
 * IP22 boardcache is not compatible with board caches.  Thus we disable it
 * during romvec action.  Since r4xx0.c is always compiled and linked with your
 * kernel, this shouldn't cause any harm regardless what MIPS processor you
 * have.
 *
 * The ARC write and read functions seem to interfere with the serial lines
 * in some way. You should be careful with them.
 */

void prom_putchar(char c)
{
	ULONG cnt;
	CHAR it = c;

	bc_disable();
	ArcWrite(1, &it, 1, &cnt);
	bc_enable();
}

char prom_getchar(void)
{
	ULONG cnt;
	CHAR c;

	bc_disable();
	ArcRead(0, &c, 1, &cnt);
	bc_enable();

	return c;
}
