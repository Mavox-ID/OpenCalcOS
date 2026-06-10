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
#ifndef _SS_SIDTAB_H_
#define _SS_SIDTAB_H_

#include "context.h"

struct sidtab_node {
	u32 sid;		/* security identifier */
	struct context context;	/* security context structure */
	struct sidtab_node *next;
};

#define SIDTAB_HASH_BITS 7
#define SIDTAB_HASH_BUCKETS (1 << SIDTAB_HASH_BITS)
#define SIDTAB_HASH_MASK (SIDTAB_HASH_BUCKETS-1)

#define SIDTAB_SIZE SIDTAB_HASH_BUCKETS

struct sidtab {
	struct sidtab_node **htable;
	unsigned int nel;	/* number of elements */
	unsigned int next_sid;	/* next SID to allocate */
	unsigned char shutdown;
#define SIDTAB_CACHE_LEN	3
	struct sidtab_node *cache[SIDTAB_CACHE_LEN];
	spinlock_t lock;
};

int sidtab_init(struct sidtab *s);
int sidtab_insert(struct sidtab *s, u32 sid, struct context *context);
struct context *sidtab_search(struct sidtab *s, u32 sid);
struct context *sidtab_search_force(struct sidtab *s, u32 sid);

int sidtab_map(struct sidtab *s,
	       int (*apply) (u32 sid,
			     struct context *context,
			     void *args),
	       void *args);

int sidtab_context_to_sid(struct sidtab *s,
			  struct context *context,
			  u32 *sid);

void sidtab_hash_eval(struct sidtab *h, char *tag);
void sidtab_destroy(struct sidtab *s);
void sidtab_set(struct sidtab *dst, struct sidtab *src);
void sidtab_shutdown(struct sidtab *s);

#endif	/* _SS_SIDTAB_H_ */


