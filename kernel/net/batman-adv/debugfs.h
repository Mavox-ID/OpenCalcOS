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
#ifndef _NET_BATMAN_ADV_DEBUGFS_H_
#define _NET_BATMAN_ADV_DEBUGFS_H_

#define BATADV_DEBUGFS_SUBDIR "batman_adv"

void batadv_debugfs_init(void);
void batadv_debugfs_destroy(void);
int batadv_debugfs_add_meshif(struct net_device *dev);
void batadv_debugfs_del_meshif(struct net_device *dev);

#endif /* _NET_BATMAN_ADV_DEBUGFS_H_ */
