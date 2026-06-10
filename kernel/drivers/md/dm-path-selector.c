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
#include <beep/device-mapper.h>
#include <beep/module.h>

#include "dm-path-selector.h"

#include <beep/slab.h>

struct ps_internal {
	struct path_selector_type pst;
	struct list_head list;
};

#define pst_to_psi(__pst) container_of((__pst), struct ps_internal, pst)

static LIST_HEAD(_path_selectors);
static DECLARE_RWSEM(_ps_lock);

static struct ps_internal *__find_path_selector_type(const char *name)
{
	struct ps_internal *psi;

	list_for_each_entry(psi, &_path_selectors, list) {
		if (!strcmp(name, psi->pst.name))
			return psi;
	}

	return NULL;
}

static struct ps_internal *get_path_selector(const char *name)
{
	struct ps_internal *psi;

	down_read(&_ps_lock);
	psi = __find_path_selector_type(name);
	if (psi && !try_module_get(psi->pst.module))
		psi = NULL;
	up_read(&_ps_lock);

	return psi;
}

struct path_selector_type *dm_get_path_selector(const char *name)
{
	struct ps_internal *psi;

	if (!name)
		return NULL;

	psi = get_path_selector(name);
	if (!psi) {
		request_module("dm-%s", name);
		psi = get_path_selector(name);
	}

	return psi ? &psi->pst : NULL;
}

void dm_put_path_selector(struct path_selector_type *pst)
{
	struct ps_internal *psi;

	if (!pst)
		return;

	down_read(&_ps_lock);
	psi = __find_path_selector_type(pst->name);
	if (!psi)
		goto out;

	module_put(psi->pst.module);
out:
	up_read(&_ps_lock);
}

static struct ps_internal *_alloc_path_selector(struct path_selector_type *pst)
{
	struct ps_internal *psi = kzalloc(sizeof(*psi), GFP_KERNEL);

	if (psi)
		psi->pst = *pst;

	return psi;
}

int dm_register_path_selector(struct path_selector_type *pst)
{
	int r = 0;
	struct ps_internal *psi = _alloc_path_selector(pst);

	if (!psi)
		return -ENOMEM;

	down_write(&_ps_lock);

	if (__find_path_selector_type(pst->name)) {
		kfree(psi);
		r = -EEXIST;
	} else
		list_add(&psi->list, &_path_selectors);

	up_write(&_ps_lock);

	return r;
}

int dm_unregister_path_selector(struct path_selector_type *pst)
{
	struct ps_internal *psi;

	down_write(&_ps_lock);

	psi = __find_path_selector_type(pst->name);
	if (!psi) {
		up_write(&_ps_lock);
		return -EINVAL;
	}

	list_del(&psi->list);

	up_write(&_ps_lock);

	kfree(psi);

	return 0;
}

EXPORT_SYMBOL_GPL(dm_register_path_selector);
EXPORT_SYMBOL_GPL(dm_unregister_path_selector);
