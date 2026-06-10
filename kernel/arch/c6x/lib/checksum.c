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
#include <net/checksum.h>

#include <asm/byteorder.h>

/*
 * copy from fs while checksumming, otherwise like csum_partial
 */
__wsum
csum_partial_copy_from_user(const void __user *src, void *dst, int len,
			    __wsum sum, int *csum_err)
{
	int missing;

	missing = __copy_from_user(dst, src, len);
	if (missing) {
		memset(dst + len - missing, 0, missing);
		*csum_err = -EFAULT;
	} else
		*csum_err = 0;

	return csum_partial(dst, len, sum);
}
EXPORT_SYMBOL(csum_partial_copy_from_user);

/* These are from csum_64plus.S */
EXPORT_SYMBOL(csum_partial);
EXPORT_SYMBOL(csum_partial_copy);
EXPORT_SYMBOL(ip_compute_csum);
EXPORT_SYMBOL(ip_fast_csum);
