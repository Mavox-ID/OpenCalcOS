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

void *memmove(void *dest, const void *src, size_t n)
{
	void *xdest = dest;
	size_t temp;

	if (!n)
		return xdest;

	if (dest < src) {
		if ((long)dest & 1) {
			char *cdest = dest;
			const char *csrc = src;
			*cdest++ = *csrc++;
			dest = cdest;
			src = csrc;
			n--;
		}
		if (n > 2 && (long)dest & 2) {
			short *sdest = dest;
			const short *ssrc = src;
			*sdest++ = *ssrc++;
			dest = sdest;
			src = ssrc;
			n -= 2;
		}
		temp = n >> 2;
		if (temp) {
			long *ldest = dest;
			const long *lsrc = src;
			temp--;
			do
				*ldest++ = *lsrc++;
			while (temp--);
			dest = ldest;
			src = lsrc;
		}
		if (n & 2) {
			short *sdest = dest;
			const short *ssrc = src;
			*sdest++ = *ssrc++;
			dest = sdest;
			src = ssrc;
		}
		if (n & 1) {
			char *cdest = dest;
			const char *csrc = src;
			*cdest = *csrc;
		}
	} else {
		dest = (char *)dest + n;
		src = (const char *)src + n;
		if ((long)dest & 1) {
			char *cdest = dest;
			const char *csrc = src;
			*--cdest = *--csrc;
			dest = cdest;
			src = csrc;
			n--;
		}
		if (n > 2 && (long)dest & 2) {
			short *sdest = dest;
			const short *ssrc = src;
			*--sdest = *--ssrc;
			dest = sdest;
			src = ssrc;
			n -= 2;
		}
		temp = n >> 2;
		if (temp) {
			long *ldest = dest;
			const long *lsrc = src;
			temp--;
			do
				*--ldest = *--lsrc;
			while (temp--);
			dest = ldest;
			src = lsrc;
		}
		if (n & 2) {
			short *sdest = dest;
			const short *ssrc = src;
			*--sdest = *--ssrc;
			dest = sdest;
			src = ssrc;
		}
		if (n & 1) {
			char *cdest = dest;
			const char *csrc = src;
			*--cdest = *--csrc;
		}
	}
	return xdest;
}
EXPORT_SYMBOL(memmove);
