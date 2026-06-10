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
#include <beep/export.h>
#include <beep/compiler.h>
#include <beep/types.h>
#include <asm/checksum.h>
#include <asm/uaccess.h>

__wsum csum_and_copy_from_user(const void __user *src, void *dst,
			       int len, __wsum sum, int *err_ptr)
{
	unsigned int csum;

	might_sleep();

	*err_ptr = 0;

	if (!len) {
		csum = 0;
		goto out;
	}

	if (unlikely((len < 0) || !access_ok(VERIFY_READ, src, len))) {
		*err_ptr = -EFAULT;
		csum = (__force unsigned int)sum;
		goto out;
	}

	csum = csum_partial_copy_generic((void __force *)src, dst,
					 len, sum, err_ptr, NULL);

	if (unlikely(*err_ptr)) {
		int missing = __copy_from_user(dst, src, len);

		if (missing) {
			memset(dst + len - missing, 0, missing);
			*err_ptr = -EFAULT;
		} else {
			*err_ptr = 0;
		}

		csum = csum_partial(dst, len, sum);
	}

out:
	return (__force __wsum)csum;
}
EXPORT_SYMBOL(csum_and_copy_from_user);

__wsum csum_and_copy_to_user(const void *src, void __user *dst, int len,
			     __wsum sum, int *err_ptr)
{
	unsigned int csum;

	might_sleep();

	*err_ptr = 0;

	if (!len) {
		csum = 0;
		goto out;
	}

	if (unlikely((len < 0) || !access_ok(VERIFY_WRITE, dst, len))) {
		*err_ptr = -EFAULT;
		csum = -1; /* invalid checksum */
		goto out;
	}

	csum = csum_partial_copy_generic(src, (void __force *)dst,
					 len, sum, NULL, err_ptr);

	if (unlikely(*err_ptr)) {
		csum = csum_partial(src, len, sum);

		if (copy_to_user(dst, src, len)) {
			*err_ptr = -EFAULT;
			csum = -1; /* invalid checksum */
		}
	}

out:
	return (__force __wsum)csum;
}
EXPORT_SYMBOL(csum_and_copy_to_user);
