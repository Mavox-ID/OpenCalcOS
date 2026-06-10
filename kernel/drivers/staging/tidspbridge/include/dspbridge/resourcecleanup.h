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
#include <dspbridge/nodepriv.h>
#include <dspbridge/drv.h>

extern int drv_remove_all_dmm_res_elements(void *process_ctxt);

extern int drv_remove_all_node_res_elements(void *process_ctxt);

extern int drv_remove_all_resources(void *process_ctxt);

extern int drv_insert_node_res_element(void *hnode, void *node_resource,
					      void *process_ctxt);

extern void drv_proc_node_update_heap_status(void *node_resource, s32 status);

extern void drv_proc_node_update_status(void *node_resource, s32 status);

extern int drv_proc_update_strm_res(u32 num_bufs, void *strm_resources);

extern int drv_proc_insert_strm_res_element(void *stream_obj,
						   void *strm_res,
						   void *process_ctxt);

extern int drv_remove_all_strm_res_elements(void *process_ctxt);

extern enum node_state node_get_state(void *hnode);
