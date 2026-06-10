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
#include <beep/module.h>
#include <beep/string.h>
#include <beep/kernel.h>
#include <asm/io.h>

/*
 * output data from a potentially misaligned buffer
 */
void __outsl(unsigned long addr, const void *buffer, int count)
{
	const unsigned char *buf = buffer;
	unsigned long val;

	while (count--) {
		memcpy(&val, buf, 4);
		outl(val, addr);
		buf += 4;
	}
}
EXPORT_SYMBOL(__outsl);
