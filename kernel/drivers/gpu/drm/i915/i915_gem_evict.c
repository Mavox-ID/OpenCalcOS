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
#include <drm/drmP.h>
#include "i915_drv.h"
#include <drm/i915_drm.h>
#include "i915_trace.h"

static bool
mark_free(struct drm_i915_gem_object *obj, struct list_head *unwind)
{
	if (obj->pin_count)
		return false;

	list_add(&obj->exec_list, unwind);
	return drm_mm_scan_add_block(obj->gtt_space);
}

int
i915_gem_evict_something(struct drm_device *dev, int min_size,
			 unsigned alignment, unsigned cache_level,
			 bool mappable, bool nonblocking)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct list_head eviction_list, unwind_list;
	struct drm_i915_gem_object *obj;
	int ret = 0;

	trace_i915_gem_evict(dev, min_size, alignment, mappable);

	/*
	 * The goal is to evict objects and amalgamate space in LRU order.
	 * The oldest idle objects reside on the inactive list, which is in
	 * retirement order. The next objects to retire are those on the (per
	 * ring) active list that do not have an outstanding flush. Once the
	 * hardware reports completion (the seqno is updated after the
	 * batchbuffer has been finished) the clean buffer objects would
	 * be retired to the inactive list. Any dirty objects would be added
	 * to the tail of the flushing list. So after processing the clean
	 * active objects we need to emit a MI_FLUSH to retire the flushing
	 * list, hence the retirement order of the flushing list is in
	 * advance of the dirty objects on the active lists.
	 *
	 * The retirement sequence is thus:
	 *   1. Inactive objects (already retired)
	 *   2. Clean active objects
	 *   3. Flushing list
	 *   4. Dirty active objects.
	 *
	 * On each list, the oldest objects lie at the HEAD with the freshest
	 * object on the TAIL.
	 */

	INIT_LIST_HEAD(&unwind_list);
	if (mappable)
		drm_mm_init_scan_with_range(&dev_priv->mm.gtt_space,
					    min_size, alignment, cache_level,
					    0, dev_priv->mm.gtt_mappable_end);
	else
		drm_mm_init_scan(&dev_priv->mm.gtt_space,
				 min_size, alignment, cache_level);

	/* First see if there is a large enough contiguous idle region... */
	list_for_each_entry(obj, &dev_priv->mm.inactive_list, mm_list) {
		if (mark_free(obj, &unwind_list))
			goto found;
	}

	if (nonblocking)
		goto none;

	/* Now merge in the soon-to-be-expired objects... */
	list_for_each_entry(obj, &dev_priv->mm.active_list, mm_list) {
		if (mark_free(obj, &unwind_list))
			goto found;
	}

none:
	/* Nothing found, clean up and bail out! */
	while (!list_empty(&unwind_list)) {
		obj = list_first_entry(&unwind_list,
				       struct drm_i915_gem_object,
				       exec_list);

		ret = drm_mm_scan_remove_block(obj->gtt_space);
		BUG_ON(ret);

		list_del_init(&obj->exec_list);
	}

	/* We expect the caller to unpin, evict all and try again, or give up.
	 * So calling i915_gem_evict_everything() is unnecessary.
	 */
	return -ENOSPC;

found:
	/* drm_mm doesn't allow any other other operations while
	 * scanning, therefore store to be evicted objects on a
	 * temporary list. */
	INIT_LIST_HEAD(&eviction_list);
	while (!list_empty(&unwind_list)) {
		obj = list_first_entry(&unwind_list,
				       struct drm_i915_gem_object,
				       exec_list);
		if (drm_mm_scan_remove_block(obj->gtt_space)) {
			list_move(&obj->exec_list, &eviction_list);
			drm_gem_object_reference(&obj->base);
			continue;
		}
		list_del_init(&obj->exec_list);
	}

	/* Unbinding will emit any required flushes */
	while (!list_empty(&eviction_list)) {
		obj = list_first_entry(&eviction_list,
				       struct drm_i915_gem_object,
				       exec_list);
		if (ret == 0)
			ret = i915_gem_object_unbind(obj);

		list_del_init(&obj->exec_list);
		drm_gem_object_unreference(&obj->base);
	}

	return ret;
}

int
i915_gem_evict_everything(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_i915_gem_object *obj, *next;
	bool lists_empty;
	int ret;

	lists_empty = (list_empty(&dev_priv->mm.inactive_list) &&
		       list_empty(&dev_priv->mm.active_list));
	if (lists_empty)
		return -ENOSPC;

	trace_i915_gem_evict_everything(dev);

	/* The gpu_idle will flush everything in the write domain to the
	 * active list. Then we must move everything off the active list
	 * with retire requests.
	 */
	ret = i915_gpu_idle(dev);
	if (ret)
		return ret;

	i915_gem_retire_requests(dev);

	/* Having flushed everything, unbind() should never raise an error */
	list_for_each_entry_safe(obj, next,
				 &dev_priv->mm.inactive_list, mm_list)
		if (obj->pin_count == 0)
			WARN_ON(i915_gem_object_unbind(obj));

	return 0;
}
