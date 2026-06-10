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
#ifndef DVB_BT8XX_H
#define DVB_BT8XX_H

#include <beep/i2c.h>
#include <beep/mutex.h>
#include "dvbdev.h"
#include "dvb_net.h"
#include "bttv.h"
#include "mt352.h"
#include "sp887x.h"
#include "dst_common.h"
#include "nxt6000.h"
#include "cx24110.h"
#include "or51211.h"
#include "lgdt330x.h"
#include "zl10353.h"
#include "tuner-simple.h"

struct dvb_bt8xx_card {
	struct mutex lock;
	int nfeeds;
	char card_name[32];
	struct dvb_adapter dvb_adapter;
	struct bt878 *bt;
	unsigned int bttv_nr;
	struct dvb_demux demux;
	struct dmxdev dmxdev;
	struct dmx_frontend fe_hw;
	struct dmx_frontend fe_mem;
	u32 gpio_mode;
	u32 op_sync_orin;
	u32 irq_err_ignore;
	struct i2c_adapter *i2c_adapter;
	struct dvb_net dvbnet;

	struct dvb_frontend* fe;
};

#endif /* DVB_BT8XX_H */
