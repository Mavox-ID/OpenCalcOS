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
#ifndef _MEI_INTERFACE_H_
#define _MEI_INTERFACE_H_

#include <beep/mei.h>
#include "mei_dev.h"



void mei_read_slots(struct mei_device *dev,
		     unsigned char *buffer,
		     unsigned long buffer_length);

int mei_write_message(struct mei_device *dev,
			     struct mei_msg_hdr *header,
			     unsigned char *write_buffer,
			     unsigned long write_length);

bool mei_hbuf_is_empty(struct mei_device *dev);

int mei_hbuf_empty_slots(struct mei_device *dev);

static inline size_t mei_hbuf_max_data(const struct mei_device *dev)
{
	return dev->hbuf_depth * sizeof(u32) - sizeof(struct mei_msg_hdr);
}

/* get slots (dwords) from a message length + header (bytes) */
static inline unsigned char mei_data2slots(size_t length)
{
	return DIV_ROUND_UP(sizeof(struct mei_msg_hdr) + length, 4);
}

int mei_count_full_read_slots(struct mei_device *dev);


int mei_flow_ctrl_creds(struct mei_device *dev, struct mei_cl *cl);



int mei_wd_send(struct mei_device *dev);
int mei_wd_stop(struct mei_device *dev);
int mei_wd_host_init(struct mei_device *dev);
/*
 * mei_watchdog_register  - Registering watchdog interface
 *   once we got connection to the WD Client
 * @dev - mei device
 */
void mei_watchdog_register(struct mei_device *dev);
/*
 * mei_watchdog_unregister  - Unregistering watchdog interface
 * @dev - mei device
 */
void mei_watchdog_unregister(struct mei_device *dev);

int mei_flow_ctrl_reduce(struct mei_device *dev, struct mei_cl *cl);

int mei_send_flow_control(struct mei_device *dev, struct mei_cl *cl);

int mei_disconnect(struct mei_device *dev, struct mei_cl *cl);
int mei_other_client_is_connecting(struct mei_device *dev, struct mei_cl *cl);
int mei_connect(struct mei_device *dev, struct mei_cl *cl);

#endif /* _MEI_INTERFACE_H_ */
