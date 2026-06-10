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
#ifndef __IORPC_BEEP_RPC_H__
#define __IORPC_BEEP_RPC_H__

#include <hv/iorpc.h>

#include <beep/string.h>
#include <beep/module.h>
#include <asm/pgtable.h>

#define IORPC_OP_ARM_POLLFD            IORPC_OPCODE(IORPC_FORMAT_KERNEL_POLLFD, 0x9000)
#define IORPC_OP_CLOSE_POLLFD          IORPC_OPCODE(IORPC_FORMAT_KERNEL_POLLFD, 0x9001)
#define IORPC_OP_GET_MMIO_BASE         IORPC_OPCODE(IORPC_FORMAT_NONE_NOUSER, 0x8000)
#define IORPC_OP_CHECK_MMIO_OFFSET     IORPC_OPCODE(IORPC_FORMAT_NONE_NOUSER, 0x8001)

int __iorpc_arm_pollfd(int fd, int pollfd_cookie);

int __iorpc_close_pollfd(int fd, int pollfd_cookie);

int __iorpc_get_mmio_base(int fd, HV_PTE *base);

int __iorpc_check_mmio_offset(int fd, unsigned long offset, unsigned long size);

#endif /* !__IORPC_BEEP_RPC_H__ */
