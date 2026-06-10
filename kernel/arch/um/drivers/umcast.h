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
#ifndef __DRIVERS_UMCAST_H
#define __DRIVERS_UMCAST_H

#include <net_user.h>

struct umcast_data {
	char *addr;
	unsigned short lport;
	unsigned short rport;
	void *listen_addr;
	void *remote_addr;
	int ttl;
	int unicast;
	void *dev;
};

extern const struct net_user_info umcast_user_info;

extern int umcast_user_write(int fd, void *buf, int len,
			     struct umcast_data *pri);

#endif
