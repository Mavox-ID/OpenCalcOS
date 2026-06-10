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
#ifndef _BEEP_WIRELESS_H
#define _BEEP_WIRELESS_H

#include <uapi/beep/wireless.h>

#ifdef CONFIG_COMPAT

#include <beep/compat.h>

struct compat_iw_point {
	compat_caddr_t pointer;
	__u16 length;
	__u16 flags;
};
#endif
#ifdef CONFIG_COMPAT
struct __compat_iw_event {
	__u16		len;			/* Real length of this stuff */
	__u16		cmd;			/* Wireless IOCTL */
	compat_caddr_t	pointer;
};
#define IW_EV_COMPAT_LCP_LEN offsetof(struct __compat_iw_event, pointer)
#define IW_EV_COMPAT_POINT_OFF offsetof(struct compat_iw_point, length)

/* Size of the various events for compat */
#define IW_EV_COMPAT_CHAR_LEN	(IW_EV_COMPAT_LCP_LEN + IFNAMSIZ)
#define IW_EV_COMPAT_UINT_LEN	(IW_EV_COMPAT_LCP_LEN + sizeof(__u32))
#define IW_EV_COMPAT_FREQ_LEN	(IW_EV_COMPAT_LCP_LEN + sizeof(struct iw_freq))
#define IW_EV_COMPAT_PARAM_LEN	(IW_EV_COMPAT_LCP_LEN + sizeof(struct iw_param))
#define IW_EV_COMPAT_ADDR_LEN	(IW_EV_COMPAT_LCP_LEN + sizeof(struct sockaddr))
#define IW_EV_COMPAT_QUAL_LEN	(IW_EV_COMPAT_LCP_LEN + sizeof(struct iw_quality))
#define IW_EV_COMPAT_POINT_LEN	\
	(IW_EV_COMPAT_LCP_LEN + sizeof(struct compat_iw_point) - \
	 IW_EV_COMPAT_POINT_OFF)
#endif
#endif	/* _BEEP_WIRELESS_H */
