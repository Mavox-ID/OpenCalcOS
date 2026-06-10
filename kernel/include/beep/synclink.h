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
#ifndef _SYNCLINK_H_
#define _SYNCLINK_H_

#include <uapi/beep/synclink.h>

/* provide 32 bit ioctl compatibility on 64 bit systems */
#ifdef CONFIG_COMPAT
#include <beep/compat.h>
struct MGSL_PARAMS32 {
	compat_ulong_t	mode;
	unsigned char	loopback;
	unsigned short	flags;
	unsigned char	encoding;
	compat_ulong_t	clock_speed;
	unsigned char	addr_filter;
	unsigned short	crc_type;
	unsigned char	preamble_length;
	unsigned char	preamble;
	compat_ulong_t	data_rate;
	unsigned char	data_bits;
	unsigned char	stop_bits;
	unsigned char	parity;
};
#define MGSL_IOCSPARAMS32 _IOW(MGSL_MAGIC_IOC,0,struct MGSL_PARAMS32)
#define MGSL_IOCGPARAMS32 _IOR(MGSL_MAGIC_IOC,1,struct MGSL_PARAMS32)
#endif
#endif /* _SYNCLINK_H_ */
