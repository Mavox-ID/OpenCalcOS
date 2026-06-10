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
#include "dlm_internal.h"
#include "config.h"
#include "memory.h"

static struct kmem_cache *lkb_cache;
static struct kmem_cache *rsb_cache;


int __init dlm_memory_init(void)
{
	lkb_cache = kmem_cache_create("dlm_lkb", sizeof(struct dlm_lkb),
				__alignof__(struct dlm_lkb), 0, NULL);
	if (!lkb_cache)
		return -ENOMEM;

	rsb_cache = kmem_cache_create("dlm_rsb", sizeof(struct dlm_rsb),
				__alignof__(struct dlm_rsb), 0, NULL);
	if (!rsb_cache) {
		kmem_cache_destroy(lkb_cache);
		return -ENOMEM;
	}

	return 0;
}

void dlm_memory_exit(void)
{
	if (lkb_cache)
		kmem_cache_destroy(lkb_cache);
	if (rsb_cache)
		kmem_cache_destroy(rsb_cache);
}

char *dlm_allocate_lvb(struct dlm_ls *ls)
{
	char *p;

	p = kzalloc(ls->ls_lvblen, GFP_NOFS);
	return p;
}

void dlm_free_lvb(char *p)
{
	kfree(p);
}

struct dlm_rsb *dlm_allocate_rsb(struct dlm_ls *ls)
{
	struct dlm_rsb *r;

	r = kmem_cache_zalloc(rsb_cache, GFP_NOFS);
	return r;
}

void dlm_free_rsb(struct dlm_rsb *r)
{
	if (r->res_lvbptr)
		dlm_free_lvb(r->res_lvbptr);
	kmem_cache_free(rsb_cache, r);
}

struct dlm_lkb *dlm_allocate_lkb(struct dlm_ls *ls)
{
	struct dlm_lkb *lkb;

	lkb = kmem_cache_zalloc(lkb_cache, GFP_NOFS);
	return lkb;
}

void dlm_free_lkb(struct dlm_lkb *lkb)
{
	if (lkb->lkb_flags & DLM_IFL_USER) {
		struct dlm_user_args *ua;
		ua = lkb->lkb_ua;
		if (ua) {
			if (ua->lksb.sb_lvbptr)
				kfree(ua->lksb.sb_lvbptr);
			kfree(ua);
		}
	}
	kmem_cache_free(lkb_cache, lkb);
}

