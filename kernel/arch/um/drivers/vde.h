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
#ifndef __UM_VDE_H__
#define __UM_VDE_H__

struct vde_data {
	char *vde_switch;
	char *descr;
	void *args;
	void *conn;
	void *dev;
};

struct vde_init {
	char *vde_switch;
	char *descr;
	int port;
	char *group;
	int mode;
};

extern const struct net_user_info vde_user_info;

extern void vde_init_libstuff(struct vde_data *vpri, struct vde_init *init);

extern int vde_user_read(void *conn, void *buf, int len);
extern int vde_user_write(void *conn, void *buf, int len);

#endif
