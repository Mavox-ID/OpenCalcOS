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
#ifndef _OZEVENTDEF_H
#define _OZEVENTDEF_H

#define OZ_EVT_RX_FRAME		0
#define OZ_EVT_RX_PROCESS	1
#define OZ_EVT_TX_FRAME		2
#define OZ_EVT_TX_ISOC		3
#define OZ_EVT_URB_SUBMIT	4
#define OZ_EVT_URB_DONE		5
#define OZ_EVT_URB_CANCEL	6
#define OZ_EVT_CTRL_REQ		7
#define OZ_EVT_CTRL_CNF		8
#define OZ_EVT_CTRL_LOCAL	9
#define OZ_EVT_CONNECT_REQ	10
#define OZ_EVT_CONNECT_RSP	11
#define OZ_EVT_EP_CREDIT	12
#define OZ_EVT_EP_BUFFERING	13
#define OZ_EVT_TX_ISOC_DONE	14
#define OZ_EVT_TX_ISOC_DROP	15
#define OZ_EVT_TIMER_CTRL	16
#define OZ_EVT_TIMER		17
#define OZ_EVT_PD_STATE		18
#define OZ_EVT_SERVICE		19
#define OZ_EVT_DEBUG		20

struct oz_event {
	__u32 jiffies;
	__u8 evt;
	__u8 ctx1;
	__u16 ctx2;
	__u32 ctx3;
	__u32 ctx4;
};

#endif /* _OZEVENTDEF_H */
