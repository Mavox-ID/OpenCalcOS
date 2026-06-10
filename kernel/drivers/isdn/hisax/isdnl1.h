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
#define D_RCVBUFREADY	0
#define D_XMTBUFREADY	1
#define D_L1STATECHANGE	2
#define D_CLEARBUSY	3
#define D_RX_MON0	4
#define D_RX_MON1	5
#define D_TX_MON0	6
#define D_TX_MON1	7
#define E_RCVBUFREADY	8

#define B_RCVBUFREADY	0
#define B_XMTBUFREADY	1
#define B_ACKPENDING	2

__printf(2, 3)
void debugl1(struct IsdnCardState *cs, char *fmt, ...);
void DChannel_proc_xmt(struct IsdnCardState *cs);
void DChannel_proc_rcv(struct IsdnCardState *cs);
void l1_msg(struct IsdnCardState *cs, int pr, void *arg);
void l1_msg_b(struct PStack *st, int pr, void *arg);
void Logl2Frame(struct IsdnCardState *cs, struct sk_buff *skb, char *buf,
		int dir);
void BChannel_bh(struct work_struct *work);
