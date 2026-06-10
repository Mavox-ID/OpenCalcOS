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
#ifndef _ZCACHE_RAMSTER_H_
#define _ZCACHE_RAMSTER_H_

#ifdef CONFIG_RAMSTER
#include "ramster/ramster.h"
#else
static inline void ramster_init(bool x, bool y, bool z)
{
}

static inline void ramster_register_pamops(struct tmem_pamops *p)
{
}

static inline int ramster_remotify_pageframe(bool b)
{
	return 0;
}

static inline void *ramster_pampd_free(void *v, struct tmem_pool *p,
			struct tmem_oid *o, uint32_t u, bool b)
{
	return NULL;
}

static inline int ramster_do_preload_flnode(struct tmem_pool *p)
{
	return -1;
}

static inline bool pampd_is_remote(void *v)
{
	return false;
}

static inline void ramster_count_foreign_pages(bool b, int i)
{
}

static inline void ramster_cpu_up(int cpu)
{
}

static inline void ramster_cpu_down(int cpu)
{
}
#endif

#endif /* _ZCACHE_RAMSTER_H */
