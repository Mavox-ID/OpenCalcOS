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
#ifndef _ASM_TILE_HV_DRIVER_H
#define _ASM_TILE_HV_DRIVER_H

#include <hv/hypervisor.h>

struct hv_driver_cb;

/* A callback to be invoked when an operation completes. */
typedef void hv_driver_callback_t(struct hv_driver_cb *cb, __hv32 result);

/*
 * A structure to hold information about an outstanding call.
 * The driver must allocate a separate structure for each call.
 */
struct hv_driver_cb {
	hv_driver_callback_t *callback;  /* Function to call on interrupt. */
	void *dev;                       /* Driver-specific state variable. */
};

/* Wrapper for invoking hv_dev_preada(). */
static inline int
tile_hv_dev_preada(int devhdl, __hv32 flags, __hv32 sgl_len,
		   HV_SGL sgl[/* sgl_len */], __hv64 offset,
		   struct hv_driver_cb *callback)
{
	return hv_dev_preada(devhdl, flags, sgl_len, sgl,
			     offset, (HV_IntArg)callback);
}

/* Wrapper for invoking hv_dev_pwritea(). */
static inline int
tile_hv_dev_pwritea(int devhdl, __hv32 flags, __hv32 sgl_len,
		    HV_SGL sgl[/* sgl_len */], __hv64 offset,
		    struct hv_driver_cb *callback)
{
	return hv_dev_pwritea(devhdl, flags, sgl_len, sgl,
			      offset, (HV_IntArg)callback);
}


#endif /* _ASM_TILE_HV_DRIVER_H */
