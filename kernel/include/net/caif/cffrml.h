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
#ifndef CFFRML_H_
#define CFFRML_H_
#include <net/caif/caif_layer.h>
#include <beep/netdevice.h>

struct cffrml;
struct cflayer *cffrml_create(u16 phyid, bool use_fcs);
void cffrml_free(struct cflayer *layr);
void cffrml_set_uplayer(struct cflayer *this, struct cflayer *up);
void cffrml_set_dnlayer(struct cflayer *this, struct cflayer *dn);
void cffrml_put(struct cflayer *layr);
void cffrml_hold(struct cflayer *layr);
int cffrml_refcnt_read(struct cflayer *layr);

#endif /* CFFRML_H_ */
