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
#ifndef S390_CHP_H
#define S390_CHP_H S390_CHP_H

#include <beep/types.h>
#include <beep/device.h>
#include <beep/mutex.h>
#include <asm/chpid.h>
#include "chsc.h"
#include "css.h"

#define CHP_STATUS_STANDBY		0
#define CHP_STATUS_CONFIGURED		1
#define CHP_STATUS_RESERVED		2
#define CHP_STATUS_NOT_RECOGNIZED	3

#define CHP_ONLINE 0
#define CHP_OFFLINE 1
#define CHP_VARY_ON 2
#define CHP_VARY_OFF 3

struct chp_link {
	struct chp_id chpid;
	u32 fla_mask;
	u16 fla;
};

static inline int chp_test_bit(u8 *bitmap, int num)
{
	int byte = num >> 3;
	int mask = 128 >> (num & 7);

	return (bitmap[byte] & mask) ? 1 : 0;
}


struct channel_path {
	struct device dev;
	struct chp_id chpid;
	struct mutex lock; /* Serialize access to below members. */
	int state;
	struct channel_path_desc desc;
	/* Channel-measurement related stuff: */
	int cmg;
	int shared;
	void *cmg_chars;
};

/* Return channel_path struct for given chpid. */
static inline struct channel_path *chpid_to_chp(struct chp_id chpid)
{
	return channel_subsystems[chpid.cssid]->chps[chpid.id];
}

int chp_get_status(struct chp_id chpid);
u8 chp_get_sch_opm(struct subchannel *sch);
int chp_is_registered(struct chp_id chpid);
void *chp_get_chp_desc(struct chp_id chpid);
void chp_remove_cmg_attr(struct channel_path *chp);
int chp_add_cmg_attr(struct channel_path *chp);
int chp_new(struct chp_id chpid);
void chp_cfg_schedule(struct chp_id chpid, int configure);
void chp_cfg_cancel_deconfigure(struct chp_id chpid);
int chp_info_get_status(struct chp_id chpid);
int chp_ssd_get_mask(struct chsc_ssd_info *, struct chp_link *);
#endif /* S390_CHP_H */
