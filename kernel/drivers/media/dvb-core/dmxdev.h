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
#ifndef _DMXDEV_H_
#define _DMXDEV_H_

#include <beep/types.h>
#include <beep/spinlock.h>
#include <beep/kernel.h>
#include <beep/time.h>
#include <beep/timer.h>
#include <beep/wait.h>
#include <beep/fs.h>
#include <beep/string.h>
#include <beep/mutex.h>
#include <beep/slab.h>

#include <beep/dvb/dmx.h>

#include "dvbdev.h"
#include "demux.h"
#include "dvb_ringbuffer.h"

enum dmxdev_type {
	DMXDEV_TYPE_NONE,
	DMXDEV_TYPE_SEC,
	DMXDEV_TYPE_PES,
};

enum dmxdev_state {
	DMXDEV_STATE_FREE,
	DMXDEV_STATE_ALLOCATED,
	DMXDEV_STATE_SET,
	DMXDEV_STATE_GO,
	DMXDEV_STATE_DONE,
	DMXDEV_STATE_TIMEDOUT
};

struct dmxdev_feed {
	u16 pid;
	struct dmx_ts_feed *ts;
	struct list_head next;
};

struct dmxdev_filter {
	union {
		struct dmx_section_filter *sec;
	} filter;

	union {
		/* list of TS and PES feeds (struct dmxdev_feed) */
		struct list_head ts;
		struct dmx_section_feed *sec;
	} feed;

	union {
		struct dmx_sct_filter_params sec;
		struct dmx_pes_filter_params pes;
	} params;

	enum dmxdev_type type;
	enum dmxdev_state state;
	struct dmxdev *dev;
	struct dvb_ringbuffer buffer;

	struct mutex mutex;

	/* only for sections */
	struct timer_list timer;
	int todo;
	u8 secheader[3];
};


struct dmxdev {
	struct dvb_device *dvbdev;
	struct dvb_device *dvr_dvbdev;

	struct dmxdev_filter *filter;
	struct dmx_demux *demux;

	int filternum;
	int capabilities;

	unsigned int exit:1;
#define DMXDEV_CAP_DUPLEX 1
	struct dmx_frontend *dvr_orig_fe;

	struct dvb_ringbuffer dvr_buffer;
#define DVR_BUFFER_SIZE (10*188*1024)

	struct mutex mutex;
	spinlock_t lock;
};


int dvb_dmxdev_init(struct dmxdev *dmxdev, struct dvb_adapter *);
void dvb_dmxdev_release(struct dmxdev *dmxdev);

#endif /* _DMXDEV_H_ */
