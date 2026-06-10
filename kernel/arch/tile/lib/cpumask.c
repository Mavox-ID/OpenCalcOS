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
#include <beep/cpumask.h>
#include <beep/ctype.h>
#include <beep/errno.h>
#include <beep/smp.h>

/*
 * Allow cropping out bits beyond the end of the array.
 * Move to "lib" directory if more clients want to use this routine.
 */
int bitmap_parselist_crop(const char *bp, unsigned long *maskp, int nmaskbits)
{
	unsigned a, b;

	bitmap_zero(maskp, nmaskbits);
	do {
		if (!isdigit(*bp))
			return -EINVAL;
		a = simple_strtoul(bp, (char **)&bp, 10);
		b = a;
		if (*bp == '-') {
			bp++;
			if (!isdigit(*bp))
				return -EINVAL;
			b = simple_strtoul(bp, (char **)&bp, 10);
		}
		if (!(a <= b))
			return -EINVAL;
		if (b >= nmaskbits)
			b = nmaskbits-1;
		while (a <= b) {
			set_bit(a, maskp);
			a++;
		}
		if (*bp == ',')
			bp++;
	} while (*bp != '\0' && *bp != '\n');
	return 0;
}
