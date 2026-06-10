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
#ifndef _TIPC_BEARER_H
#define _TIPC_BEARER_H

#include "bcast.h"

#define MAX_BEARERS	2
#define MAX_MEDIA	2

/*
 * Identifiers associated with TIPC message header media address info
 *
 * - address info field is 20 bytes long
 * - media type identifier located at offset 3
 * - remaining bytes vary according to media type
 */
#define TIPC_MEDIA_ADDR_SIZE	20
#define TIPC_MEDIA_TYPE_OFFSET	3

/*
 * Identifiers of supported TIPC media types
 */
#define TIPC_MEDIA_TYPE_ETH	1

/**
 * struct tipc_media_addr - destination address used by TIPC bearers
 * @value: address info (format defined by media)
 * @media_id: TIPC media type identifier
 * @broadcast: non-zero if address is a broadcast address
 */
struct tipc_media_addr {
	u8 value[TIPC_MEDIA_ADDR_SIZE];
	u8 media_id;
	u8 broadcast;
};

struct tipc_bearer;

/**
 * struct tipc_media - TIPC media information available to internal users
 * @send_msg: routine which handles buffer transmission
 * @enable_bearer: routine which enables a bearer
 * @disable_bearer: routine which disables a bearer
 * @addr2str: routine which converts media address to string
 * @str2addr: routine which converts media address from string
 * @addr2msg: routine which converts media address to protocol message area
 * @msg2addr: routine which converts media address from protocol message area
 * @bcast_addr: media address used in broadcasting
 * @priority: default link (and bearer) priority
 * @tolerance: default time (in ms) before declaring link failure
 * @window: default window (in packets) before declaring link congestion
 * @type_id: TIPC media identifier
 * @name: media name
 */
struct tipc_media {
	int (*send_msg)(struct sk_buff *buf,
			struct tipc_bearer *b_ptr,
			struct tipc_media_addr *dest);
	int (*enable_bearer)(struct tipc_bearer *b_ptr);
	void (*disable_bearer)(struct tipc_bearer *b_ptr);
	int (*addr2str)(struct tipc_media_addr *a, char *str_buf, int str_size);
	int (*str2addr)(struct tipc_media_addr *a, char *str_buf);
	int (*addr2msg)(struct tipc_media_addr *a, char *msg_area);
	int (*msg2addr)(struct tipc_media_addr *a, char *msg_area);
	struct tipc_media_addr bcast_addr;
	u32 priority;
	u32 tolerance;
	u32 window;
	u32 type_id;
	char name[TIPC_MAX_MEDIA_NAME];
};

/**
 * struct tipc_bearer - TIPC bearer structure
 * @usr_handle: pointer to additional media-specific information about bearer
 * @mtu: max packet size bearer can support
 * @blocked: non-zero if bearer is blocked
 * @lock: spinlock for controlling access to bearer
 * @addr: media-specific address associated with bearer
 * @name: bearer name (format = media:interface)
 * @media: ptr to media structure associated with bearer
 * @priority: default link priority for bearer
 * @window: default window size for bearer
 * @tolerance: default link tolerance for bearer
 * @identity: array index of this bearer within TIPC bearer array
 * @link_req: ptr to (optional) structure making periodic link setup requests
 * @links: list of non-congested links associated with bearer
 * @active: non-zero if bearer structure is represents a bearer
 * @net_plane: network plane ('A' through 'H') currently associated with bearer
 * @nodes: indicates which nodes in cluster can be reached through bearer
 *
 * Note: media-specific code is responsible for initialization of the fields
 * indicated below when a bearer is enabled; TIPC's generic bearer code takes
 * care of initializing all other fields.
 */
struct tipc_bearer {
	void *usr_handle;			/* initalized by media */
	u32 mtu;				/* initalized by media */
	int blocked;				/* initalized by media */
	struct tipc_media_addr addr;		/* initalized by media */
	char name[TIPC_MAX_BEARER_NAME];
	spinlock_t lock;
	struct tipc_media *media;
	u32 priority;
	u32 window;
	u32 tolerance;
	u32 identity;
	struct tipc_link_req *link_req;
	struct list_head links;
	int active;
	char net_plane;
	struct tipc_node_map nodes;
};

struct tipc_bearer_names {
	char media_name[TIPC_MAX_MEDIA_NAME];
	char if_name[TIPC_MAX_IF_NAME];
};

struct tipc_link;

extern struct tipc_bearer tipc_bearers[];

/*
 * TIPC routines available to supported media types
 */
int tipc_register_media(struct tipc_media *m_ptr);

void tipc_recv_msg(struct sk_buff *buf, struct tipc_bearer *tb_ptr);

int  tipc_block_bearer(const char *name);
void tipc_continue(struct tipc_bearer *tb_ptr);

int tipc_enable_bearer(const char *bearer_name, u32 disc_domain, u32 priority);
int tipc_disable_bearer(const char *name);

/*
 * Routines made available to TIPC by supported media types
 */
int  tipc_eth_media_start(void);
void tipc_eth_media_stop(void);

int tipc_media_set_priority(const char *name, u32 new_value);
int tipc_media_set_window(const char *name, u32 new_value);
void tipc_media_addr_printf(char *buf, int len, struct tipc_media_addr *a);
struct sk_buff *tipc_media_get_names(void);

struct sk_buff *tipc_bearer_get_names(void);
void tipc_bearer_add_dest(struct tipc_bearer *b_ptr, u32 dest);
void tipc_bearer_remove_dest(struct tipc_bearer *b_ptr, u32 dest);
struct tipc_bearer *tipc_bearer_find(const char *name);
struct tipc_bearer *tipc_bearer_find_interface(const char *if_name);
struct tipc_media *tipc_media_find(const char *name);
int tipc_bearer_blocked(struct tipc_bearer *b_ptr);
void tipc_bearer_stop(void);

/**
 * tipc_bearer_send- sends buffer to destination over bearer
 *
 * IMPORTANT:
 * The media send routine must not alter the buffer being passed in
 * as it may be needed for later retransmission!
 */
static inline void tipc_bearer_send(struct tipc_bearer *b, struct sk_buff *buf,
				   struct tipc_media_addr *dest)
{
	b->media->send_msg(buf, b, dest);
}

#endif	/* _TIPC_BEARER_H */
