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
/*
 * Support for user memory access from kernel.  This will
 * probably be inlined for performance at some point, but
 * for ease of debug, and to a lesser degree for code size,
 * we implement here as subroutines.
 */
#include <beep/types.h>
#include <asm/uaccess.h>
#include <asm/pgtable.h>

/*
 * For clear_user(), exploit previously defined copy_to_user function
 * and the fact that we've got a handy zero page defined in kernel/head.S
 *
 * dczero here would be even faster.
 */
__kernel_size_t __clear_user_hexagon(void __user *dest, unsigned long count)
{
	long uncleared;

	while (count > PAGE_SIZE) {
		uncleared = __copy_to_user_hexagon(dest, &empty_zero_page,
						PAGE_SIZE);
		if (uncleared)
			return count - (PAGE_SIZE - uncleared);
		count -= PAGE_SIZE;
		dest += PAGE_SIZE;
	}
	if (count)
		count = __copy_to_user_hexagon(dest, &empty_zero_page, count);

	return count;
}

unsigned long clear_user_hexagon(void __user *dest, unsigned long count)
{
	if (!access_ok(VERIFY_WRITE, dest, count))
		return count;
	else
		return __clear_user_hexagon(dest, count);
}
