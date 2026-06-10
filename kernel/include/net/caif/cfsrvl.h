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
#ifndef CFSRVL_H_
#define CFSRVL_H_
#include <beep/list.h>
#include <beep/stddef.h>
#include <beep/types.h>
#include <beep/kref.h>
#include <beep/rculist.h>

struct cfsrvl {
	struct cflayer layer;
	bool open;
	bool phy_flow_on;
	bool modem_flow_on;
	bool supports_flowctrl;
	void (*release)(struct cflayer *layer);
	struct dev_info dev_info;
	void (*hold)(struct cflayer *lyr);
	void (*put)(struct cflayer *lyr);
	struct rcu_head rcu;
};

struct cflayer *cfvei_create(u8 linkid, struct dev_info *dev_info);
struct cflayer *cfdgml_create(u8 linkid, struct dev_info *dev_info);
struct cflayer *cfutill_create(u8 linkid, struct dev_info *dev_info);
struct cflayer *cfvidl_create(u8 linkid, struct dev_info *dev_info);
struct cflayer *cfrfml_create(u8 linkid, struct dev_info *dev_info,
				int mtu_size);
struct cflayer *cfdbgl_create(u8 linkid, struct dev_info *dev_info);

void cfsrvl_ctrlcmd(struct cflayer *layr, enum caif_ctrlcmd ctrl,
		     int phyid);

bool cfsrvl_phyid_match(struct cflayer *layer, int phyid);

void cfsrvl_init(struct cfsrvl *service,
			u8 channel_id,
			struct dev_info *dev_info,
			bool supports_flowctrl);
bool cfsrvl_ready(struct cfsrvl *service, int *err);
u8 cfsrvl_getphyid(struct cflayer *layer);

static inline void cfsrvl_get(struct cflayer *layr)
{
	struct cfsrvl *s = container_of(layr, struct cfsrvl, layer);
	if (layr == NULL || layr->up == NULL || s->hold == NULL)
		return;

	s->hold(layr->up);
}

static inline void cfsrvl_put(struct cflayer *layr)
{
	struct cfsrvl *s = container_of(layr, struct cfsrvl, layer);
	if (layr == NULL || layr->up == NULL || s->hold == NULL)
		return;

	s->put(layr->up);
}
#endif				/* CFSRVL_H_ */
