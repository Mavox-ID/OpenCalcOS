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
#ifndef _TIPC_REF_H
#define _TIPC_REF_H

int tipc_ref_table_init(u32 requested_size, u32 start);
void tipc_ref_table_stop(void);

u32 tipc_ref_acquire(void *object, spinlock_t **lock);
void tipc_ref_discard(u32 ref);

void *tipc_ref_lock(u32 ref);
void *tipc_ref_deref(u32 ref);

#endif
