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
#ifndef DSPDEH_
#define DSPDEH_

struct deh_mgr;
struct dev_object;
struct dsp_notification;

int bridge_deh_create(struct deh_mgr **ret_deh,
		struct dev_object *hdev_obj);

int bridge_deh_destroy(struct deh_mgr *deh);

int bridge_deh_register_notify(struct deh_mgr *deh,
		u32 event_mask,
		u32 notify_type,
		struct dsp_notification *hnotification);

void bridge_deh_notify(struct deh_mgr *deh, int event, int info);

#endif /* DSPDEH_ */
