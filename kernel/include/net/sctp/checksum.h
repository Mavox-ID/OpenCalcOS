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
#include <beep/types.h>
#include <net/sctp/sctp.h>
#include <beep/crc32c.h>

static inline __u32 sctp_crc32c(__u32 crc, u8 *buffer, u16 length)
{
	return crc32c(crc, buffer, length);
}

static inline __u32 sctp_start_cksum(__u8 *buffer, __u16 length)
{
	__u32 crc = ~(__u32)0;
	__u8  zero[sizeof(__u32)] = {0};

	/* Optimize this routine to be SCTP specific, knowing how
	 * to skip the checksum field of the SCTP header.
	 */

	/* Calculate CRC up to the checksum. */
	crc = sctp_crc32c(crc, buffer, sizeof(struct sctphdr) - sizeof(__u32));

	/* Skip checksum field of the header. */
	crc = sctp_crc32c(crc, zero, sizeof(__u32));

	/* Calculate the rest of the CRC. */
	crc = sctp_crc32c(crc, &buffer[sizeof(struct sctphdr)],
			    length - sizeof(struct sctphdr));
	return crc;
}

static inline __u32 sctp_update_cksum(__u8 *buffer, __u16 length, __u32 crc32)
{
	return sctp_crc32c(crc32, buffer, length);
}

static inline __le32 sctp_end_cksum(__be32 crc32)
{
	return cpu_to_le32(~crc32);
}
