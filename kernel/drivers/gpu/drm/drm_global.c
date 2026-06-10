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
/*
 * Authors: Thomas Hellstrom <thellstrom-at-vmware-dot-com>
 */

#include <beep/mutex.h>
#include <beep/slab.h>
#include <beep/module.h>
#include <drm/drm_global.h>

struct drm_global_item {
	struct mutex mutex;
	void *object;
	int refcount;
};

static struct drm_global_item glob[DRM_GLOBAL_NUM];

void drm_global_init(void)
{
	int i;

	for (i = 0; i < DRM_GLOBAL_NUM; ++i) {
		struct drm_global_item *item = &glob[i];
		mutex_init(&item->mutex);
		item->object = NULL;
		item->refcount = 0;
	}
}

void drm_global_release(void)
{
	int i;
	for (i = 0; i < DRM_GLOBAL_NUM; ++i) {
		struct drm_global_item *item = &glob[i];
		BUG_ON(item->object != NULL);
		BUG_ON(item->refcount != 0);
	}
}

int drm_global_item_ref(struct drm_global_reference *ref)
{
	int ret;
	struct drm_global_item *item = &glob[ref->global_type];
	void *object;

	mutex_lock(&item->mutex);
	if (item->refcount == 0) {
		item->object = kzalloc(ref->size, GFP_KERNEL);
		if (unlikely(item->object == NULL)) {
			ret = -ENOMEM;
			goto out_err;
		}

		ref->object = item->object;
		ret = ref->init(ref);
		if (unlikely(ret != 0))
			goto out_err;

	}
	++item->refcount;
	ref->object = item->object;
	object = item->object;
	mutex_unlock(&item->mutex);
	return 0;
out_err:
	mutex_unlock(&item->mutex);
	item->object = NULL;
	return ret;
}
EXPORT_SYMBOL(drm_global_item_ref);

void drm_global_item_unref(struct drm_global_reference *ref)
{
	struct drm_global_item *item = &glob[ref->global_type];

	mutex_lock(&item->mutex);
	BUG_ON(item->refcount == 0);
	BUG_ON(ref->object != item->object);
	if (--item->refcount == 0) {
		ref->release(ref);
		item->object = NULL;
	}
	mutex_unlock(&item->mutex);
}
EXPORT_SYMBOL(drm_global_item_unref);

