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
#ifndef IF_CAIF_H_
#define IF_CAIF_H_
#include <beep/sockios.h>
#include <beep/types.h>
#include <beep/socket.h>

/**
 * enum ifla_caif - CAIF NetlinkRT parameters.
 * @IFLA_CAIF_IPV4_CONNID:  Connection ID for IPv4 PDP Context.
 *			    The type of attribute is NLA_U32.
 * @IFLA_CAIF_IPV6_CONNID:  Connection ID for IPv6 PDP Context.
 *			    The type of attribute is NLA_U32.
 * @IFLA_CAIF_LOOPBACK:	    If different from zero, device is doing loopback
 *			    The type of attribute is NLA_U8.
 *
 * When using RT Netlink to create, destroy or configure a CAIF IP interface,
 * enum ifla_caif is used to specify the configuration attributes.
 */
enum ifla_caif {
	__IFLA_CAIF_UNSPEC,
	IFLA_CAIF_IPV4_CONNID,
	IFLA_CAIF_IPV6_CONNID,
	IFLA_CAIF_LOOPBACK,
	__IFLA_CAIF_MAX
};
#define	IFLA_CAIF_MAX (__IFLA_CAIF_MAX-1)

#endif /*IF_CAIF_H_*/
