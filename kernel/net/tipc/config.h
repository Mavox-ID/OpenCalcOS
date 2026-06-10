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
#ifndef _TIPC_CONFIG_H
#define _TIPC_CONFIG_H

/* ---------------------------------------------------------------------- */

#include "link.h"

struct sk_buff *tipc_cfg_reply_alloc(int payload_size);
int tipc_cfg_append_tlv(struct sk_buff *buf, int tlv_type,
			void *tlv_data, int tlv_data_size);
struct sk_buff *tipc_cfg_reply_string_type(u16 tlv_type, char *string);

static inline struct sk_buff *tipc_cfg_reply_none(void)
{
	return tipc_cfg_reply_alloc(0);
}

static inline struct sk_buff *tipc_cfg_reply_error_string(char *string)
{
	return tipc_cfg_reply_string_type(TIPC_TLV_ERROR_STRING, string);
}

static inline struct sk_buff *tipc_cfg_reply_ultra_string(char *string)
{
	return tipc_cfg_reply_string_type(TIPC_TLV_ULTRA_STRING, string);
}

struct sk_buff *tipc_cfg_do_cmd(u32 orig_node, u16 cmd,
				const void *req_tlv_area, int req_tlv_space,
				int headroom);

int  tipc_cfg_init(void);
void tipc_cfg_reinit(void);
void tipc_cfg_stop(void);

#endif
