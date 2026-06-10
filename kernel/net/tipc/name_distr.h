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
#ifndef _TIPC_NAME_DISTR_H
#define _TIPC_NAME_DISTR_H

#include "name_table.h"

void tipc_named_publish(struct publication *publ);
void tipc_named_withdraw(struct publication *publ);
void tipc_named_node_up(unsigned long node);
void tipc_named_recv(struct sk_buff *buf);
void tipc_named_reinit(void);

#endif
