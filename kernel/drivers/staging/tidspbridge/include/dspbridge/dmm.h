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
#ifndef DMM_
#define DMM_

#include <dspbridge/dbdefs.h>

struct dmm_object;

/* DMM attributes used in dmm_create() */
struct dmm_mgrattrs {
	u32 reserved;
};

#define DMMPOOLSIZE      0x4000000

/*
 *  ======== dmm_get_handle ========
 *  Purpose:
 *      Return the dynamic memory manager object for this device.
 *      This is typically called from the client process.
 */

extern int dmm_get_handle(void *hprocessor,
				 struct dmm_object **dmm_manager);

extern int dmm_reserve_memory(struct dmm_object *dmm_mgr,
				     u32 size, u32 *prsv_addr);

extern int dmm_un_reserve_memory(struct dmm_object *dmm_mgr,
					u32 rsv_addr);

extern int dmm_map_memory(struct dmm_object *dmm_mgr, u32 addr,
				 u32 size);

extern int dmm_un_map_memory(struct dmm_object *dmm_mgr,
				    u32 addr, u32 *psize);

extern int dmm_destroy(struct dmm_object *dmm_mgr);

extern int dmm_delete_tables(struct dmm_object *dmm_mgr);

extern int dmm_create(struct dmm_object **dmm_manager,
			     struct dev_object *hdev_obj,
			     const struct dmm_mgrattrs *mgr_attrts);

extern int dmm_create_tables(struct dmm_object *dmm_mgr,
				    u32 addr, u32 size);

#ifdef DSP_DMM_DEBUG
u32 dmm_mem_map_dump(struct dmm_object *dmm_mgr);
#endif

#endif /* DMM_ */
