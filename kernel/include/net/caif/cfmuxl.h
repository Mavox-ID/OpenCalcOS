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
#ifndef CFMUXL_H_
#define CFMUXL_H_
#include <net/caif/caif_layer.h>

struct cfsrvl;
struct cffrml;

struct cflayer *cfmuxl_create(void);
int cfmuxl_set_uplayer(struct cflayer *layr, struct cflayer *up, u8 linkid);
struct cflayer *cfmuxl_remove_dnlayer(struct cflayer *layr, u8 phyid);
int cfmuxl_set_dnlayer(struct cflayer *layr, struct cflayer *up, u8 phyid);
struct cflayer *cfmuxl_remove_uplayer(struct cflayer *layr, u8 linkid);

#endif				/* CFMUXL_H_ */
