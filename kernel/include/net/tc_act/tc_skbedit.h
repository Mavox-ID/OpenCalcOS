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
#ifndef __NET_TC_SKBEDIT_H
#define __NET_TC_SKBEDIT_H

#include <net/act_api.h>

struct tcf_skbedit {
	struct tcf_common	common;
	u32			flags;
	u32     		priority;
	u32     		mark;
	u16			queue_mapping;
	/* XXX: 16-bit pad here? */
};
#define to_skbedit(pc) \
	container_of(pc, struct tcf_skbedit, common)

#endif /* __NET_TC_SKBEDIT_H */
