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
#include <beep/types.h>
#include <beep/string.h>

#include <net/checksum.h>
#include <asm/byteorder.h>
#include <asm/uaccess.h>

/*
 * Copy while checksumming, otherwise like csum_partial
 */
__wsum
csum_partial_copy_nocheck (const void *src, void *dst, int len, __wsum sum)
{
	sum = csum_partial(src, len, sum);
	memcpy(dst, src, len);

	return sum;
}
EXPORT_SYMBOL(csum_partial_copy_nocheck);

/*
 * Copy from userspace and compute checksum.  If we catch an exception
 * then zero the rest of the buffer.
 */
__wsum
csum_partial_copy_from_user (const void __user *src, void *dst,
			     int len, __wsum sum, int *err_ptr)
{
	int missing;

	missing = copy_from_user(dst, src, len);
	if (missing) {
		memset(dst + len - missing, 0, missing);
		*err_ptr = -EFAULT;
	}

	return csum_partial(dst, len-missing, sum);
}
EXPORT_SYMBOL(csum_partial_copy_from_user);
EXPORT_SYMBOL(csum_partial);
