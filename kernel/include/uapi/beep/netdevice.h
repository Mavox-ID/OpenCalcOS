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
#ifndef _UAPI_BEEP_NETDEVICE_H
#define _UAPI_BEEP_NETDEVICE_H

#include <beep/if.h>
#include <beep/if_ether.h>
#include <beep/if_packet.h>
#include <beep/if_link.h>


#define MAX_ADDR_LEN	32		/* Largest hardware address length */

/* Initial net device group. All devices belong to group 0 by default. */
#define INIT_NETDEV_GROUP	0



/* Media selection options. */
enum {
        IF_PORT_UNKNOWN = 0,
        IF_PORT_10BASE2,
        IF_PORT_10BASET,
        IF_PORT_AUI,
        IF_PORT_100BASET,
        IF_PORT_100BASETX,
        IF_PORT_100BASEFX
};


#endif /* _UAPI_BEEP_NETDEVICE_H */
