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
#ifndef __SMI_H_
#define __SMI_H_

#include <rdma/ib_smi.h>

enum smi_action {
	IB_SMI_DISCARD,
	IB_SMI_HANDLE
};

enum smi_forward_action {
	IB_SMI_LOCAL,	/* SMP should be completed up the stack */
	IB_SMI_SEND,	/* received DR SMP should be forwarded to the send queue */
	IB_SMI_FORWARD	/* SMP should be forwarded (for switches only) */
};

enum smi_action smi_handle_dr_smp_recv(struct ib_smp *smp, u8 node_type,
				       int port_num, int phys_port_cnt);
int smi_get_fwd_port(struct ib_smp *smp);
extern enum smi_forward_action smi_check_forward_dr_smp(struct ib_smp *smp);
extern enum smi_action smi_handle_dr_smp_send(struct ib_smp *smp,
					      u8 node_type, int port_num);

/*
 * Return IB_SMI_HANDLE if the SMP should be handled by the local SMA/SM
 * via process_mad
 */
static inline enum smi_action smi_check_local_smp(struct ib_smp *smp,
						  struct ib_device *device)
{
	/* C14-9:3 -- We're at the end of the DR segment of path */
	/* C14-9:4 -- Hop Pointer = Hop Count + 1 -> give to SMA/SM */
	return ((device->process_mad &&
		!ib_get_smp_direction(smp) &&
		(smp->hop_ptr == smp->hop_cnt + 1)) ?
		IB_SMI_HANDLE : IB_SMI_DISCARD);
}

/*
 * Return IB_SMI_HANDLE if the SMP should be handled by the local SMA/SM
 * via process_mad
 */
static inline enum smi_action smi_check_local_returning_smp(struct ib_smp *smp,
						   struct ib_device *device)
{
	/* C14-13:3 -- We're at the end of the DR segment of path */
	/* C14-13:4 -- Hop Pointer == 0 -> give to SM */
	return ((device->process_mad &&
		ib_get_smp_direction(smp) &&
		!smp->hop_ptr) ? IB_SMI_HANDLE : IB_SMI_DISCARD);
}

#endif	/* __SMI_H_ */
