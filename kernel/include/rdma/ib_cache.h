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
#ifndef _IB_CACHE_H
#define _IB_CACHE_H

#include <rdma/ib_verbs.h>

/**
 * ib_get_cached_gid - Returns a cached GID table entry
 * @device: The device to query.
 * @port_num: The port number of the device to query.
 * @index: The index into the cached GID table to query.
 * @gid: The GID value found at the specified index.
 *
 * ib_get_cached_gid() fetches the specified GID table entry stored in
 * the local software cache.
 */
int ib_get_cached_gid(struct ib_device    *device,
		      u8                   port_num,
		      int                  index,
		      union ib_gid        *gid);

/**
 * ib_find_cached_gid - Returns the port number and GID table index where
 *   a specified GID value occurs.
 * @device: The device to query.
 * @gid: The GID value to search for.
 * @port_num: The port number of the device where the GID value was found.
 * @index: The index into the cached GID table where the GID was found.  This
 *   parameter may be NULL.
 *
 * ib_find_cached_gid() searches for the specified GID value in
 * the local software cache.
 */
int ib_find_cached_gid(struct ib_device *device,
		       union ib_gid	*gid,
		       u8               *port_num,
		       u16              *index);

/**
 * ib_get_cached_pkey - Returns a cached PKey table entry
 * @device: The device to query.
 * @port_num: The port number of the device to query.
 * @index: The index into the cached PKey table to query.
 * @pkey: The PKey value found at the specified index.
 *
 * ib_get_cached_pkey() fetches the specified PKey table entry stored in
 * the local software cache.
 */
int ib_get_cached_pkey(struct ib_device    *device_handle,
		       u8                   port_num,
		       int                  index,
		       u16                 *pkey);

/**
 * ib_find_cached_pkey - Returns the PKey table index where a specified
 *   PKey value occurs.
 * @device: The device to query.
 * @port_num: The port number of the device to search for the PKey.
 * @pkey: The PKey value to search for.
 * @index: The index into the cached PKey table where the PKey was found.
 *
 * ib_find_cached_pkey() searches the specified PKey table in
 * the local software cache.
 */
int ib_find_cached_pkey(struct ib_device    *device,
			u8                   port_num,
			u16                  pkey,
			u16                 *index);

/**
 * ib_find_exact_cached_pkey - Returns the PKey table index where a specified
 *   PKey value occurs. Comparison uses the FULL 16 bits (incl membership bit)
 * @device: The device to query.
 * @port_num: The port number of the device to search for the PKey.
 * @pkey: The PKey value to search for.
 * @index: The index into the cached PKey table where the PKey was found.
 *
 * ib_find_exact_cached_pkey() searches the specified PKey table in
 * the local software cache.
 */
int ib_find_exact_cached_pkey(struct ib_device    *device,
			      u8                   port_num,
			      u16                  pkey,
			      u16                 *index);

/**
 * ib_get_cached_lmc - Returns a cached lmc table entry
 * @device: The device to query.
 * @port_num: The port number of the device to query.
 * @lmc: The lmc value for the specified port for that device.
 *
 * ib_get_cached_lmc() fetches the specified lmc table entry stored in
 * the local software cache.
 */
int ib_get_cached_lmc(struct ib_device *device,
		      u8                port_num,
		      u8                *lmc);

#endif /* _IB_CACHE_H */
