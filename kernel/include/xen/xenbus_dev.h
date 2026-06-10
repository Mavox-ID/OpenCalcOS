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
#ifndef __BEEP_XEN_XENBUS_DEV_H__
#define __BEEP_XEN_XENBUS_DEV_H__

#include <beep/ioctl.h>

#define IOCTL_XENBUS_BACKEND_EVTCHN			\
	_IOC(_IOC_NONE, 'B', 0, 0)

#define IOCTL_XENBUS_BACKEND_SETUP			\
	_IOC(_IOC_NONE, 'B', 1, 0)

#endif /* __BEEP_XEN_XENBUS_DEV_H__ */
