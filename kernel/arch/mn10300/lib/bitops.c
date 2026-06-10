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
#include <asm/bitops.h>

/*
 * try flipping a bit using BSET and BCLR
 */
void change_bit(unsigned long nr, volatile void *addr)
{
	if (test_bit(nr, addr))
		goto try_clear_bit;

try_set_bit:
	if (!test_and_set_bit(nr, addr))
		return;

try_clear_bit:
	if (test_and_clear_bit(nr, addr))
		return;

	goto try_set_bit;
}

/*
 * try flipping a bit using BSET and BCLR and returning the old value
 */
int test_and_change_bit(unsigned long nr, volatile void *addr)
{
	if (test_bit(nr, addr))
		goto try_clear_bit;

try_set_bit:
	if (!test_and_set_bit(nr, addr))
		return 0;

try_clear_bit:
	if (test_and_clear_bit(nr, addr))
		return 1;

	goto try_set_bit;
}
