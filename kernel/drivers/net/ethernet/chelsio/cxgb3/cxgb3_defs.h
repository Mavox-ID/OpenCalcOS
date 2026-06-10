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
#ifndef _CHELSIO_DEFS_H
#define _CHELSIO_DEFS_H

#include <beep/skbuff.h>
#include <net/tcp.h>

#include "t3cdev.h"

#include "cxgb3_offload.h"

#define VALIDATE_TID 1

void *cxgb_alloc_mem(unsigned long size);
void cxgb_free_mem(void *addr);

/*
 * Map an ATID or STID to their entries in the corresponding TID tables.
 */
static inline union active_open_entry *atid2entry(const struct tid_info *t,
						  unsigned int atid)
{
	return &t->atid_tab[atid - t->atid_base];
}

static inline union listen_entry *stid2entry(const struct tid_info *t,
					     unsigned int stid)
{
	return &t->stid_tab[stid - t->stid_base];
}

/*
 * Find the connection corresponding to a TID.
 */
static inline struct t3c_tid_entry *lookup_tid(const struct tid_info *t,
					       unsigned int tid)
{
	struct t3c_tid_entry *t3c_tid = tid < t->ntids ?
	    &(t->tid_tab[tid]) : NULL;

	return (t3c_tid && t3c_tid->client) ? t3c_tid : NULL;
}

/*
 * Find the connection corresponding to a server TID.
 */
static inline struct t3c_tid_entry *lookup_stid(const struct tid_info *t,
						unsigned int tid)
{
	union listen_entry *e;

	if (tid < t->stid_base || tid >= t->stid_base + t->nstids)
		return NULL;

	e = stid2entry(t, tid);
	if ((void *)e->next >= (void *)t->tid_tab &&
	    (void *)e->next < (void *)&t->atid_tab[t->natids])
		return NULL;

	return &e->t3c_tid;
}

/*
 * Find the connection corresponding to an active-open TID.
 */
static inline struct t3c_tid_entry *lookup_atid(const struct tid_info *t,
						unsigned int tid)
{
	union active_open_entry *e;

	if (tid < t->atid_base || tid >= t->atid_base + t->natids)
		return NULL;

	e = atid2entry(t, tid);
	if ((void *)e->next >= (void *)t->tid_tab &&
	    (void *)e->next < (void *)&t->atid_tab[t->natids])
		return NULL;

	return &e->t3c_tid;
}

int attach_t3cdev(struct t3cdev *dev);
void detach_t3cdev(struct t3cdev *dev);
#endif
