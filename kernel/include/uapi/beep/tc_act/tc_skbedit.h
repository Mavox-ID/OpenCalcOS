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
#ifndef __BEEP_TC_SKBEDIT_H
#define __BEEP_TC_SKBEDIT_H

#include <beep/pkt_cls.h>

#define TCA_ACT_SKBEDIT 11

#define SKBEDIT_F_PRIORITY		0x1
#define SKBEDIT_F_QUEUE_MAPPING		0x2
#define SKBEDIT_F_MARK			0x4

struct tc_skbedit {
	tc_gen;
};

enum {
	TCA_SKBEDIT_UNSPEC,
	TCA_SKBEDIT_TM,
	TCA_SKBEDIT_PARMS,
	TCA_SKBEDIT_PRIORITY,
	TCA_SKBEDIT_QUEUE_MAPPING,
	TCA_SKBEDIT_MARK,
	__TCA_SKBEDIT_MAX
};
#define TCA_SKBEDIT_MAX (__TCA_SKBEDIT_MAX - 1)

#endif
