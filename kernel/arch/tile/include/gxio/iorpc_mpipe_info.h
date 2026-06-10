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
#ifndef __GXIO_MPIPE_INFO_BEEP_RPC_H__
#define __GXIO_MPIPE_INFO_BEEP_RPC_H__

#include <hv/iorpc.h>

#include <hv/drv_mpipe_intf.h>
#include <asm/page.h>
#include <gxio/kiorpc.h>
#include <gxio/mpipe.h>
#include <beep/string.h>
#include <beep/module.h>
#include <asm/pgtable.h>


#define GXIO_MPIPE_INFO_OP_ENUMERATE_AUX IORPC_OPCODE(IORPC_FORMAT_NONE, 0x1251)
#define GXIO_MPIPE_INFO_OP_GET_MMIO_BASE IORPC_OPCODE(IORPC_FORMAT_NONE_NOUSER, 0x8000)
#define GXIO_MPIPE_INFO_OP_CHECK_MMIO_OFFSET IORPC_OPCODE(IORPC_FORMAT_NONE_NOUSER, 0x8001)


int gxio_mpipe_info_enumerate_aux(gxio_mpipe_info_context_t * context,
				  unsigned int idx,
				  _gxio_mpipe_link_name_t * name,
				  _gxio_mpipe_link_mac_t * mac);

int gxio_mpipe_info_get_mmio_base(gxio_mpipe_info_context_t * context,
				  HV_PTE *base);

int gxio_mpipe_info_check_mmio_offset(gxio_mpipe_info_context_t * context,
				      unsigned long offset, unsigned long size);

#endif /* !__GXIO_MPIPE_INFO_BEEP_RPC_H__ */
