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

#ifndef _TTM_EXECBUF_UTIL_H_
#define _TTM_EXECBUF_UTIL_H_

#include <ttm/ttm_bo_api.h>
#include <beep/list.h>

/**
 * struct ttm_validate_buffer
 *
 * @head:           list head for thread-private list.
 * @bo:             refcounted buffer object pointer.
 * @reserved:       Indicates whether @bo has been reserved for validation.
 * @removed:        Indicates whether @bo has been removed from lru lists.
 * @put_count:      Number of outstanding references on bo::list_kref.
 * @old_sync_obj:   Pointer to a sync object about to be unreferenced
 */

struct ttm_validate_buffer {
	struct list_head head;
	struct ttm_buffer_object *bo;
	bool reserved;
	bool removed;
	int put_count;
	void *old_sync_obj;
};

/**
 * function ttm_eu_backoff_reservation
 *
 * @list:     thread private list of ttm_validate_buffer structs.
 *
 * Undoes all buffer validation reservations for bos pointed to by
 * the list entries.
 */

extern void ttm_eu_backoff_reservation(struct list_head *list);

/**
 * function ttm_eu_reserve_buffers
 *
 * @list:    thread private list of ttm_validate_buffer structs.
 *
 * Tries to reserve bos pointed to by the list entries for validation.
 * If the function returns 0, all buffers are marked as "unfenced",
 * taken off the lru lists and are not synced for write CPU usage.
 *
 * If the function detects a deadlock due to multiple threads trying to
 * reserve the same buffers in reverse order, all threads except one will
 * back off and retry. This function may sleep while waiting for
 * CPU write reservations to be cleared, and for other threads to
 * unreserve their buffers.
 *
 * This function may return -ERESTART or -EAGAIN if the calling process
 * receives a signal while waiting. In that case, no buffers on the list
 * will be reserved upon return.
 *
 * Buffers reserved by this function should be unreserved by
 * a call to either ttm_eu_backoff_reservation() or
 * ttm_eu_fence_buffer_objects() when command submission is complete or
 * has failed.
 */

extern int ttm_eu_reserve_buffers(struct list_head *list);

/**
 * function ttm_eu_fence_buffer_objects.
 *
 * @list:        thread private list of ttm_validate_buffer structs.
 * @sync_obj:    The new sync object for the buffers.
 *
 * This function should be called when command submission is complete, and
 * it will add a new sync object to bos pointed to by entries on @list.
 * It also unreserves all buffers, putting them on lru lists.
 *
 */

extern void ttm_eu_fence_buffer_objects(struct list_head *list, void *sync_obj);

#endif
