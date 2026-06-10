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
#ifndef __INC_ETHERNET_H
#define __INC_ETHERNET_H

#define ETHERNET_ADDRESS_LENGTH		6	/*!< Ethernet Address Length*/
#define ETHERNET_HEADER_SIZE		14	/*!< Ethernet Header Length*/
#define LLC_HEADER_SIZE			6	/*!< LLC Header Length*/
#define TYPE_LENGTH_FIELD_SIZE		2	/*!< Type/Length Size*/
#define MINIMUM_ETHERNET_PACKET_SIZE	60	/*!< Min Ethernet Packet Size*/
#define MAXIMUM_ETHERNET_PACKET_SIZE	1514	/*!< Max Ethernet Packet Size*/

/*!< Is Multicast Address? */
#define RT_ETH_IS_MULTICAST(_pAddr)	((((u8 *)(_pAddr))[0]&0x01) != 0)

#endif /* #ifndef __INC_ETHERNET_H */

