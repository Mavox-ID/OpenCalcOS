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
#ifndef _TIPC_DISCOVER_H
#define _TIPC_DISCOVER_H

struct tipc_link_req;

int tipc_disc_create(struct tipc_bearer *b_ptr, struct tipc_media_addr *dest,
		     u32 dest_domain);
void tipc_disc_delete(struct tipc_link_req *req);
void tipc_disc_add_dest(struct tipc_link_req *req);
void tipc_disc_remove_dest(struct tipc_link_req *req);
void tipc_disc_recv_msg(struct sk_buff *buf, struct tipc_bearer *b_ptr);

#endif
