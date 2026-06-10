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
#ifndef WRAPPER_H
#define WRAPPER_H

#include <beep/types.h>
#include <beep/skbuff.h>
#include <beep/netdevice.h>

#include <net/irda/irda_device.h>	/* iobuff_t */

#define BOF  0xc0 /* Beginning of frame */
#define XBOF 0xff
#define EOF  0xc1 /* End of frame */
#define CE   0x7d /* Control escape */

#define STA BOF  /* Start flag */
#define STO EOF  /* End flag */

#define IRDA_TRANS 0x20    /* Asynchronous transparency modifier */       

/* States for receiving a frame in async mode */
enum {
	OUTSIDE_FRAME, 
	BEGIN_FRAME, 
	LINK_ESCAPE, 
	INSIDE_FRAME
};

/* Proto definitions */
int async_wrap_skb(struct sk_buff *skb, __u8 *tx_buff, int buffsize);
void async_unwrap_char(struct net_device *dev, struct net_device_stats *stats,
		       iobuff_t *buf, __u8 byte);

#endif
