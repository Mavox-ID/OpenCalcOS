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
#ifndef _OZCDEV_H
#define _OZCDEV_H

int oz_cdev_register(void);
int oz_cdev_deregister(void);
int oz_cdev_init(void);
void oz_cdev_term(void);
int oz_cdev_start(struct oz_pd *pd, int resume);
void oz_cdev_stop(struct oz_pd *pd, int pause);
void oz_cdev_rx(struct oz_pd *pd, struct oz_elt *elt);
void oz_cdev_heartbeat(struct oz_pd *pd);

#endif /* _OZCDEV_H */
