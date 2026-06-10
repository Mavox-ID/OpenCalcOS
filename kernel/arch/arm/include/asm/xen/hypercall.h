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
#ifndef _ASM_ARM_XEN_HYPERCALL_H
#define _ASM_ARM_XEN_HYPERCALL_H

#include <xen/interface/xen.h>

long privcmd_call(unsigned call, unsigned long a1,
		unsigned long a2, unsigned long a3,
		unsigned long a4, unsigned long a5);
int HYPERVISOR_xen_version(int cmd, void *arg);
int HYPERVISOR_console_io(int cmd, int count, char *str);
int HYPERVISOR_grant_table_op(unsigned int cmd, void *uop, unsigned int count);
int HYPERVISOR_sched_op(int cmd, void *arg);
int HYPERVISOR_event_channel_op(int cmd, void *arg);
unsigned long HYPERVISOR_hvm_op(int op, void *arg);
int HYPERVISOR_memory_op(unsigned int cmd, void *arg);
int HYPERVISOR_physdev_op(int cmd, void *arg);

static inline void
MULTI_update_va_mapping(struct multicall_entry *mcl, unsigned long va,
			unsigned int new_val, unsigned long flags)
{
	BUG();
}

static inline void
MULTI_mmu_update(struct multicall_entry *mcl, struct mmu_update *req,
		 int count, int *success_count, domid_t domid)
{
	BUG();
}

static inline int
HYPERVISOR_multicall(void *call_list, int nr_calls)
{
	BUG();
}
#endif /* _ASM_ARM_XEN_HYPERCALL_H */
