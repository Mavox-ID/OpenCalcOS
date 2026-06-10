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
#ifndef _OZUSBSVC_H
#define _OZUSBSVC_H

/*------------------------------------------------------------------------------
 * Per PD context info stored in application context area of PD.
 * This object is reference counted to ensure it doesn't disappear while
 * still in use.
 */
struct oz_usb_ctx {
	atomic_t ref_count;
	u8 tx_seq_num;
	u8 rx_seq_num;
	struct oz_pd *pd;
	void *hport;
	int stopped;
};

int oz_usb_init(void);
void oz_usb_term(void);
int oz_usb_start(struct oz_pd *pd, int resume);
void oz_usb_stop(struct oz_pd *pd, int pause);
void oz_usb_rx(struct oz_pd *pd, struct oz_elt *elt);
int oz_usb_heartbeat(struct oz_pd *pd);
void oz_usb_farewell(struct oz_pd *pd, u8 ep_num, u8 *data, u8 len);

#endif /* _OZUSBSVC_H */

