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
#ifndef _NET_BATMAN_ADV_GATEWAY_COMMON_H_
#define _NET_BATMAN_ADV_GATEWAY_COMMON_H_

enum batadv_gw_modes {
	BATADV_GW_MODE_OFF,
	BATADV_GW_MODE_CLIENT,
	BATADV_GW_MODE_SERVER,
};

#define BATADV_GW_MODE_OFF_NAME	"off"
#define BATADV_GW_MODE_CLIENT_NAME	"client"
#define BATADV_GW_MODE_SERVER_NAME	"server"

void batadv_gw_bandwidth_to_kbit(uint8_t gw_class, int *down, int *up);
ssize_t batadv_gw_bandwidth_set(struct net_device *net_dev, char *buff,
				size_t count);

#endif /* _NET_BATMAN_ADV_GATEWAY_COMMON_H_ */
