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
#ifndef __OSDEP_INTF_H_
#define __OSDEP_INTF_H_

#include "osdep_service.h"
#include "drv_types.h"

#define RND4(x)	(((x >> 2) + (((x & 3) == 0) ?  0 : 1)) << 2)

struct intf_priv {
	u8 *intf_dev;
	/* when in USB, IO is through interrupt in/out endpoints */
	struct usb_device *udev;
	struct urb *piorw_urb;
	struct semaphore io_retevt;
};

int r871x_ioctl(struct net_device *dev, struct ifreq *rq, int cmd);

#endif	/*_OSDEP_INTF_H_*/
