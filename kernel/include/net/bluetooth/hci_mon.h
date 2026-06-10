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
#ifndef __HCI_MON_H
#define __HCI_MON_H

struct hci_mon_hdr {
	__le16	opcode;
	__le16	index;
	__le16	len;
} __packed;
#define HCI_MON_HDR_SIZE 6

#define HCI_MON_NEW_INDEX	0
#define HCI_MON_DEL_INDEX	1
#define HCI_MON_COMMAND_PKT	2
#define HCI_MON_EVENT_PKT	3
#define HCI_MON_ACL_TX_PKT	4
#define HCI_MON_ACL_RX_PKT	5
#define HCI_MON_SCO_TX_PKT	6
#define HCI_MON_SCO_RX_PKT	7

struct hci_mon_new_index {
	__u8		type;
	__u8		bus;
	bdaddr_t	bdaddr;
	char		name[8];
} __packed;
#define HCI_MON_NEW_INDEX_SIZE 16

#endif /* __HCI_MON_H */
