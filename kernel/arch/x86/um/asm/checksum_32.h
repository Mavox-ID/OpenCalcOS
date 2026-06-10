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
#ifndef __UM_SYSDEP_CHECKSUM_H
#define __UM_SYSDEP_CHECKSUM_H

static inline __sum16 ip_compute_csum(const void *buff, int len)
{
    return csum_fold (csum_partial(buff, len, 0));
}

#define _HAVE_ARCH_IPV6_CSUM
static __inline__ __sum16 csum_ipv6_magic(const struct in6_addr *saddr,
					  const struct in6_addr *daddr,
					  __u32 len, unsigned short proto,
					  __wsum sum)
{
	__asm__(
		"addl 0(%1), %0		;\n"
		"adcl 4(%1), %0		;\n"
		"adcl 8(%1), %0		;\n"
		"adcl 12(%1), %0	;\n"
		"adcl 0(%2), %0		;\n"
		"adcl 4(%2), %0		;\n"
		"adcl 8(%2), %0		;\n"
		"adcl 12(%2), %0	;\n"
		"adcl %3, %0		;\n"
		"adcl %4, %0		;\n"
		"adcl $0, %0		;\n"
		: "=&r" (sum)
		: "r" (saddr), "r" (daddr),
		  "r"(htonl(len)), "r"(htonl(proto)), "0"(sum));

	return csum_fold(sum);
}

/*
 *	Copy and checksum to user
 */
#define HAVE_CSUM_COPY_USER
static __inline__ __wsum csum_and_copy_to_user(const void *src,
						     void __user *dst,
						     int len, __wsum sum, int *err_ptr)
{
	if (access_ok(VERIFY_WRITE, dst, len)) {
		if (copy_to_user(dst, src, len)) {
			*err_ptr = -EFAULT;
			return (__force __wsum)-1;
		}

		return csum_partial(src, len, sum);
	}

	if (len)
		*err_ptr = -EFAULT;

	return (__force __wsum)-1; /* invalid checksum */
}

#endif
