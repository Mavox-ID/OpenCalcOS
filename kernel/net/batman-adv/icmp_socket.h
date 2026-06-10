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
#ifndef _NET_BATMAN_ADV_ICMP_SOCKET_H_
#define _NET_BATMAN_ADV_ICMP_SOCKET_H_

#define BATADV_ICMP_SOCKET "socket"

void batadv_socket_init(void);
int batadv_socket_setup(struct batadv_priv *bat_priv);
void batadv_socket_receive_packet(struct batadv_icmp_packet_rr *icmp_packet,
				  size_t icmp_len);

#endif /* _NET_BATMAN_ADV_ICMP_SOCKET_H_ */
