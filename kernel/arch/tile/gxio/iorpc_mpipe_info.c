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
/* This file is machine-generated; DO NOT EDIT! */
#include "gxio/iorpc_mpipe_info.h"


struct enumerate_aux_param {
	_gxio_mpipe_link_name_t name;
	_gxio_mpipe_link_mac_t mac;
};

int gxio_mpipe_info_enumerate_aux(gxio_mpipe_info_context_t * context,
				  unsigned int idx,
				  _gxio_mpipe_link_name_t * name,
				  _gxio_mpipe_link_mac_t * mac)
{
	int __result;
	struct enumerate_aux_param temp;
	struct enumerate_aux_param *params = &temp;

	__result =
	    hv_dev_pread(context->fd, 0, (HV_VirtAddr) params, sizeof(*params),
			 (((uint64_t) idx << 32) |
			  GXIO_MPIPE_INFO_OP_ENUMERATE_AUX));
	*name = params->name;
	*mac = params->mac;

	return __result;
}

EXPORT_SYMBOL(gxio_mpipe_info_enumerate_aux);

struct get_mmio_base_param {
	HV_PTE base;
};

int gxio_mpipe_info_get_mmio_base(gxio_mpipe_info_context_t * context,
				  HV_PTE *base)
{
	int __result;
	struct get_mmio_base_param temp;
	struct get_mmio_base_param *params = &temp;

	__result =
	    hv_dev_pread(context->fd, 0, (HV_VirtAddr) params, sizeof(*params),
			 GXIO_MPIPE_INFO_OP_GET_MMIO_BASE);
	*base = params->base;

	return __result;
}

EXPORT_SYMBOL(gxio_mpipe_info_get_mmio_base);

struct check_mmio_offset_param {
	unsigned long offset;
	unsigned long size;
};

int gxio_mpipe_info_check_mmio_offset(gxio_mpipe_info_context_t * context,
				      unsigned long offset, unsigned long size)
{
	struct check_mmio_offset_param temp;
	struct check_mmio_offset_param *params = &temp;

	params->offset = offset;
	params->size = size;

	return hv_dev_pwrite(context->fd, 0, (HV_VirtAddr) params,
			     sizeof(*params),
			     GXIO_MPIPE_INFO_OP_CHECK_MMIO_OFFSET);
}

EXPORT_SYMBOL(gxio_mpipe_info_check_mmio_offset);
