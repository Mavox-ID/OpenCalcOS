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
#ifndef _OMAP_RPMSG_H
#define _OMAP_RPMSG_H

/*
 * enum - Predefined Mailbox Messages
 *
 * @RP_MBOX_READY: informs the M3's that we're up and running. this is
 * part of the init sequence sent that the M3 expects to see immediately
 * after it is booted.
 *
 * @RP_MBOX_PENDING_MSG: informs the receiver that there is an inbound
 * message waiting in its own receive-side vring. please note that currently
 * this message is optional: alternatively, one can explicitly send the index
 * of the triggered virtqueue itself. the preferred approach will be decided
 * as we progress and experiment with those two different approaches.
 *
 * @RP_MBOX_CRASH: this message is sent if BIOS crashes
 *
 * @RP_MBOX_ECHO_REQUEST: a mailbox-level "ping" message.
 *
 * @RP_MBOX_ECHO_REPLY: a mailbox-level reply to a "ping"
 *
 * @RP_MBOX_ABORT_REQUEST: a "please crash" request, used for testing the
 * recovery mechanism (to some extent).
 */
enum omap_rp_mbox_messages {
	RP_MBOX_READY		= 0xFFFFFF00,
	RP_MBOX_PENDING_MSG	= 0xFFFFFF01,
	RP_MBOX_CRASH		= 0xFFFFFF02,
	RP_MBOX_ECHO_REQUEST	= 0xFFFFFF03,
	RP_MBOX_ECHO_REPLY	= 0xFFFFFF04,
	RP_MBOX_ABORT_REQUEST	= 0xFFFFFF05,
};

#endif /* _OMAP_RPMSG_H */
