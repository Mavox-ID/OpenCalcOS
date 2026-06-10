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
#ifndef _OZPROTO_H
#define _OZPROTO_H

#include <asm/byteorder.h>
#include "ozconfig.h"
#include "ozappif.h"

#define OZ_ALLOCATED_SPACE(__x)	(LL_RESERVED_SPACE(__x)+(__x)->needed_tailroom)

/* Converts millisecs to jiffies.
 */
#define oz_ms_to_jiffies(__x)	msecs_to_jiffies(__x)

/* Quantum milliseconds.
 */
#define OZ_QUANTUM_MS		8
/* Quantum jiffies
 */
#define OZ_QUANTUM_J		(oz_ms_to_jiffies(OZ_QUANTUM_MS))
/* Default timeouts.
 */
#define OZ_CONNECTION_TOUT_J	(2*HZ)
#define OZ_PRESLEEP_TOUT_J	(11*HZ)

/* Maximun sizes of tx frames. */
#define OZ_MAX_TX_SIZE		1514

/* Maximum number of uncompleted isoc frames that can be pending in network. */
#define OZ_MAX_SUBMITTED_ISOC	16

/* Maximum number of uncompleted isoc frames that can be pending in Tx Queue. */
#define OZ_MAX_TX_QUEUE_ISOC	32

/* Application handler functions.
 */
typedef int (*oz_app_init_fn_t)(void);
typedef void (*oz_app_term_fn_t)(void);
typedef int (*oz_app_start_fn_t)(struct oz_pd *pd, int resume);
typedef void (*oz_app_stop_fn_t)(struct oz_pd *pd, int pause);
typedef void (*oz_app_rx_fn_t)(struct oz_pd *pd, struct oz_elt *elt);
typedef int (*oz_app_hearbeat_fn_t)(struct oz_pd *pd);
typedef void (*oz_app_farewell_fn_t)(struct oz_pd *pd, u8 ep_num,
			u8 *data, u8 len);

struct oz_app_if {
	oz_app_init_fn_t	init;
	oz_app_term_fn_t	term;
	oz_app_start_fn_t	start;
	oz_app_stop_fn_t	stop;
	oz_app_rx_fn_t		rx;
	oz_app_hearbeat_fn_t	heartbeat;
	oz_app_farewell_fn_t	farewell;
	int			app_id;
};

int oz_protocol_init(char *devs);
void oz_protocol_term(void);
int oz_get_pd_list(struct oz_mac_addr *addr, int max_count);
void oz_app_enable(int app_id, int enable);
struct oz_pd *oz_pd_find(u8 *mac_addr);
void oz_binding_add(char *net_dev);
void oz_binding_remove(char *net_dev);
void oz_timer_add(struct oz_pd *pd, int type, unsigned long due_time,
		int remove);
void oz_timer_delete(struct oz_pd *pd, int type);
void oz_pd_request_heartbeat(struct oz_pd *pd);
void oz_polling_lock_bh(void);
void oz_polling_unlock_bh(void);

#endif /* _OZPROTO_H */
