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
#ifndef _CORE_PRIV_H
#define _CORE_PRIV_H

#include <beep/list.h>
#include <beep/spinlock.h>

#include <rdma/ib_verbs.h>

int  ib_device_register_sysfs(struct ib_device *device,
			      int (*port_callback)(struct ib_device *,
						   u8, struct kobject *));
void ib_device_unregister_sysfs(struct ib_device *device);

int  ib_sysfs_setup(void);
void ib_sysfs_cleanup(void);

int  ib_cache_setup(void);
void ib_cache_cleanup(void);

#endif /* _CORE_PRIV_H */
