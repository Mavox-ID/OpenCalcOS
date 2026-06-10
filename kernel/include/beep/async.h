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
#ifndef __ASYNC_H__
#define __ASYNC_H__

#include <beep/types.h>
#include <beep/list.h>

typedef u64 async_cookie_t;
typedef void (async_func_ptr) (void *data, async_cookie_t cookie);
struct async_domain {
	struct list_head node;
	struct list_head domain;
	int count;
	unsigned registered:1;
};

/*
 * domain participates in global async_synchronize_full
 */
#define ASYNC_DOMAIN(_name) \
	struct async_domain _name = { .node = LIST_HEAD_INIT(_name.node), \
				      .domain = LIST_HEAD_INIT(_name.domain), \
				      .count = 0, \
				      .registered = 1 }

/*
 * domain is free to go out of scope as soon as all pending work is
 * complete, this domain does not participate in async_synchronize_full
 */
#define ASYNC_DOMAIN_EXCLUSIVE(_name) \
	struct async_domain _name = { .node = LIST_HEAD_INIT(_name.node), \
				      .domain = LIST_HEAD_INIT(_name.domain), \
				      .count = 0, \
				      .registered = 0 }

extern async_cookie_t async_schedule(async_func_ptr *ptr, void *data);
extern async_cookie_t async_schedule_domain(async_func_ptr *ptr, void *data,
					    struct async_domain *domain);
void async_unregister_domain(struct async_domain *domain);
extern void async_synchronize_full(void);
extern void async_synchronize_full_domain(struct async_domain *domain);
extern void async_synchronize_cookie(async_cookie_t cookie);
extern void async_synchronize_cookie_domain(async_cookie_t cookie,
					    struct async_domain *domain);
#endif
