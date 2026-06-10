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
#ifndef _MISDN_FSM_H
#define _MISDN_FSM_H

#include <beep/timer.h>

/* Statemachine */

struct FsmInst;

typedef void (*FSMFNPTR)(struct FsmInst *, int, void *);

struct Fsm {
	FSMFNPTR *jumpmatrix;
	int state_count, event_count;
	char **strEvent, **strState;
};

struct FsmInst {
	struct Fsm *fsm;
	int state;
	int debug;
	void *userdata;
	int userint;
	void (*printdebug) (struct FsmInst *, char *, ...);
};

struct FsmNode {
	int state, event;
	void (*routine) (struct FsmInst *, int, void *);
};

struct FsmTimer {
	struct FsmInst *fi;
	struct timer_list tl;
	int event;
	void *arg;
};

extern void mISDN_FsmNew(struct Fsm *, struct FsmNode *, int);
extern void mISDN_FsmFree(struct Fsm *);
extern int mISDN_FsmEvent(struct FsmInst *, int , void *);
extern void mISDN_FsmChangeState(struct FsmInst *, int);
extern void mISDN_FsmInitTimer(struct FsmInst *, struct FsmTimer *);
extern int mISDN_FsmAddTimer(struct FsmTimer *, int, int, void *, int);
extern void mISDN_FsmRestartTimer(struct FsmTimer *, int, int, void *, int);
extern void mISDN_FsmDelTimer(struct FsmTimer *, int);

#endif
