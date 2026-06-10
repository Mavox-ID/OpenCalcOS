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
#ifndef _VMWGFX_RESOURCE_PRIV_H_
#define _VMWGFX_RESOURCE_PRIV_H_

#include "vmwgfx_drv.h"

/**
 * struct vmw_user_resource_conv - Identify a derived user-exported resource
 * type and provide a function to convert its ttm_base_object pointer to
 * a struct vmw_resource
 */
struct vmw_user_resource_conv {
	enum ttm_object_type object_type;
	struct vmw_resource *(*base_obj_to_res)(struct ttm_base_object *base);
	void (*res_free) (struct vmw_resource *res);
};

/**
 * struct vmw_res_func - members and functions common for a resource type
 *
 * @res_type:          Enum that identifies the lru list to use for eviction.
 * @needs_backup:      Whether the resource is guest-backed and needs
 *                     persistent buffer storage.
 * @type_name:         String that identifies the resource type.
 * @backup_placement:  TTM placement for backup buffers.
 * @may_evict          Whether the resource may be evicted.
 * @create:            Create a hardware resource.
 * @destroy:           Destroy a hardware resource.
 * @bind:              Bind a hardware resource to persistent buffer storage.
 * @unbind:            Unbind a hardware resource from persistent
 *                     buffer storage.
 */

struct vmw_res_func {
	enum vmw_res_type res_type;
	bool needs_backup;
	const char *type_name;
	struct ttm_placement *backup_placement;
	bool may_evict;

	int (*create) (struct vmw_resource *res);
	int (*destroy) (struct vmw_resource *res);
	int (*bind) (struct vmw_resource *res,
		     struct ttm_validate_buffer *val_buf);
	int (*unbind) (struct vmw_resource *res,
		       bool readback,
		       struct ttm_validate_buffer *val_buf);
};

int vmw_resource_alloc_id(struct vmw_resource *res);
void vmw_resource_release_id(struct vmw_resource *res);
int vmw_resource_init(struct vmw_private *dev_priv, struct vmw_resource *res,
		      bool delay_id,
		      void (*res_free) (struct vmw_resource *res),
		      const struct vmw_res_func *func);
void vmw_resource_activate(struct vmw_resource *res,
			   void (*hw_destroy) (struct vmw_resource *));
#endif
