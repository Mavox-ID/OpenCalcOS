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
#define SBIT(state) (1 << state)
#define ALL_STATES  0x03ffffff

#define PROTO_DIS_EURO	0x08

#define L3_DEB_WARN	0x01
#define L3_DEB_PROTERR	0x02
#define L3_DEB_STATE	0x04
#define L3_DEB_CHARGE	0x08
#define L3_DEB_CHECK	0x10
#define L3_DEB_SI	0x20

struct stateentry {
	int state;
	int primitive;
	void (*rout) (struct l3_process *, u8, void *);
};

#define l3_debug(st, fmt, args...) HiSax_putstatus(st->l1.hardware, "l3 ", fmt, ## args)

struct PStack;

void newl3state(struct l3_process *pc, int state);
void L3InitTimer(struct l3_process *pc, struct L3Timer *t);
void L3DelTimer(struct L3Timer *t);
int L3AddTimer(struct L3Timer *t, int millisec, int event);
void StopAllL3Timer(struct l3_process *pc);
struct sk_buff *l3_alloc_skb(int len);
struct l3_process *new_l3_process(struct PStack *st, int cr);
void release_l3_process(struct l3_process *p);
struct l3_process *getl3proc(struct PStack *st, int cr);
void l3_msg(struct PStack *st, int pr, void *arg);
void setstack_dss1(struct PStack *st);
void setstack_ni1(struct PStack *st);
void setstack_1tr6(struct PStack *st);
