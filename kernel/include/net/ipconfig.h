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
/* The following are initdata: */

extern int ic_proto_enabled;	/* Protocols enabled (see IC_xxx) */
extern int ic_set_manually;	/* IPconfig parameters set manually */

extern __be32 ic_myaddr;		/* My IP address */
extern __be32 ic_gateway;		/* Gateway IP address */

extern __be32 ic_servaddr;		/* Boot server IP address */

extern __be32 root_server_addr;	/* Address of NFS server */
extern u8 root_server_path[];	/* Path to mount as root */


/* bits in ic_proto_{enabled,used} */
#define IC_PROTO	0xFF	/* Protocols mask: */
#define IC_BOOTP	0x01	/*   BOOTP (or DHCP, see below) */
#define IC_RARP		0x02	/*   RARP */
#define IC_USE_DHCP    0x100	/* If on, use DHCP instead of BOOTP */
