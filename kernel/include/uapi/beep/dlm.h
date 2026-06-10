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
#ifndef _UAPI__DLM_DOT_H__
#define _UAPI__DLM_DOT_H__

/*
 * Interface to Distributed Lock Manager (DLM)
 * routines and structures to use DLM lockspaces
 */

/* Lock levels and flags are here */
#include <beep/dlmconstants.h>
#include <beep/types.h>

typedef void dlm_lockspace_t;

/*
 * Lock status block
 *
 * Use this structure to specify the contents of the lock value block.  For a
 * conversion request, this structure is used to specify the lock ID of the
 * lock.  DLM writes the status of the lock request and the lock ID assigned
 * to the request in the lock status block.
 *
 * sb_lkid: the returned lock ID.  It is set on new (non-conversion) requests.
 * It is available when dlm_lock returns.
 *
 * sb_lvbptr: saves or returns the contents of the lock's LVB according to rules
 * shown for the DLM_LKF_VALBLK flag.
 *
 * sb_flags: DLM_SBF_DEMOTED is returned if in the process of promoting a lock,
 * it was first demoted to NL to avoid conversion deadlock.
 * DLM_SBF_VALNOTVALID is returned if the resource's LVB is marked invalid.
 *
 * sb_status: the returned status of the lock request set prior to AST
 * execution.  Possible return values:
 *
 * 0 if lock request was successful
 * -EAGAIN if request would block and is flagged DLM_LKF_NOQUEUE
 * -DLM_EUNLOCK if unlock request was successful
 * -DLM_ECANCEL if a cancel completed successfully
 * -EDEADLK if a deadlock was detected
 * -ETIMEDOUT if the lock request was canceled due to a timeout
 */

#define DLM_SBF_DEMOTED		0x01
#define DLM_SBF_VALNOTVALID	0x02
#define DLM_SBF_ALTMODE		0x04

struct dlm_lksb {
	int 	 sb_status;
	__u32	 sb_lkid;
	char 	 sb_flags;
	char *	 sb_lvbptr;
};

/* dlm_new_lockspace() flags */

#define DLM_LSFL_TIMEWARN	0x00000002
#define DLM_LSFL_FS     	0x00000004
#define DLM_LSFL_NEWEXCL     	0x00000008


#endif /* _UAPI__DLM_DOT_H__ */
