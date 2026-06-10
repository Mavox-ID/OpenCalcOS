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
#ifndef _UAPI_ASM_POWERPC_EPAPR_HCALLS_H
#define _UAPI_ASM_POWERPC_EPAPR_HCALLS_H

#define EV_BYTE_CHANNEL_SEND		1
#define EV_BYTE_CHANNEL_RECEIVE		2
#define EV_BYTE_CHANNEL_POLL		3
#define EV_INT_SET_CONFIG		4
#define EV_INT_GET_CONFIG		5
#define EV_INT_SET_MASK			6
#define EV_INT_GET_MASK			7
#define EV_INT_IACK			9
#define EV_INT_EOI			10
#define EV_INT_SEND_IPI			11
#define EV_INT_SET_TASK_PRIORITY	12
#define EV_INT_GET_TASK_PRIORITY	13
#define EV_DOORBELL_SEND		14
#define EV_MSGSND			15
#define EV_IDLE				16

/* vendor ID: epapr */
#define EV_LOCAL_VENDOR_ID		0	/* for private use */
#define EV_EPAPR_VENDOR_ID		1
#define EV_FSL_VENDOR_ID		2	/* Freescale Semiconductor */
#define EV_IBM_VENDOR_ID		3	/* IBM */
#define EV_GHS_VENDOR_ID		4	/* Green Hills Software */
#define EV_ENEA_VENDOR_ID		5	/* Enea */
#define EV_WR_VENDOR_ID			6	/* Wind River Systems */
#define EV_AMCC_VENDOR_ID		7	/* Applied Micro Circuits */
#define EV_KVM_VENDOR_ID		42	/* KVM */

/* The max number of bytes that a byte channel can send or receive per call */
#define EV_BYTE_CHANNEL_MAX_BYTES	16


#define _EV_HCALL_TOKEN(id, num) (((id) << 16) | (num))
#define EV_HCALL_TOKEN(hcall_num) _EV_HCALL_TOKEN(EV_EPAPR_VENDOR_ID, hcall_num)

/* epapr return codes */
#define EV_SUCCESS		0
#define EV_EPERM		1	/* Operation not permitted */
#define EV_ENOENT		2	/*  Entry Not Found */
#define EV_EIO			3	/* I/O error occured */
#define EV_EAGAIN		4	/* The operation had insufficient
					 * resources to complete and should be
					 * retried
					 */
#define EV_ENOMEM		5	/* There was insufficient memory to
					 * complete the operation */
#define EV_EFAULT		6	/* Bad guest address */
#define EV_ENODEV		7	/* No such device */
#define EV_EINVAL		8	/* An argument supplied to the hcall
					   was out of range or invalid */
#define EV_INTERNAL		9	/* An internal error occured */
#define EV_CONFIG		10	/* A configuration error was detected */
#define EV_INVALID_STATE	11	/* The object is in an invalid state */
#define EV_UNIMPLEMENTED	12	/* Unimplemented hypercall */
#define EV_BUFFER_OVERFLOW	13	/* Caller-supplied buffer too small */

#endif /* _UAPI_ASM_POWERPC_EPAPR_HCALLS_H */
