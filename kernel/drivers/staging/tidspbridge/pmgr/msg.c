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
#include <beep/types.h>

/*  ----------------------------------- Host OS */
#include <dspbridge/host_os.h>

/*  ----------------------------------- DSP/BIOS Bridge */
#include <dspbridge/dbdefs.h>

/*  ----------------------------------- Bridge Driver */
#include <dspbridge/dspdefs.h>

/*  ----------------------------------- Platform Manager */
#include <dspbridge/dev.h>

/*  ----------------------------------- This */
#include <msgobj.h>
#include <dspbridge/msg.h>

/*
 *  ======== msg_create ========
 *  Purpose:
 *      Create an object to manage message queues. Only one of these objects
 *      can exist per device object.
 */
int msg_create(struct msg_mgr **msg_man,
		      struct dev_object *hdev_obj, msg_onexit msg_callback)
{
	struct bridge_drv_interface *intf_fxns;
	struct msg_mgr_ *msg_mgr_obj;
	struct msg_mgr *hmsg_mgr;
	int status = 0;

	*msg_man = NULL;

	dev_get_intf_fxns(hdev_obj, &intf_fxns);

	/* Let Bridge message module finish the create: */
	status =
	    (*intf_fxns->msg_create) (&hmsg_mgr, hdev_obj, msg_callback);

	if (!status) {
		/* Fill in DSP API message module's fields of the msg_mgr
		 * structure */
		msg_mgr_obj = (struct msg_mgr_ *)hmsg_mgr;
		msg_mgr_obj->intf_fxns = intf_fxns;

		/* Finally, return the new message manager handle: */
		*msg_man = hmsg_mgr;
	} else {
		status = -EPERM;
	}
	return status;
}

/*
 *  ======== msg_delete ========
 *  Purpose:
 *      Delete a msg_ctrl manager allocated in msg_create().
 */
void msg_delete(struct msg_mgr *hmsg_mgr)
{
	struct msg_mgr_ *msg_mgr_obj = (struct msg_mgr_ *)hmsg_mgr;
	struct bridge_drv_interface *intf_fxns;

	if (msg_mgr_obj) {
		intf_fxns = msg_mgr_obj->intf_fxns;

		/* Let Bridge message module destroy the msg_mgr: */
		(*intf_fxns->msg_delete) (hmsg_mgr);
	} else {
		dev_dbg(bridge, "%s: Error hmsg_mgr handle: %p\n",
			__func__, hmsg_mgr);
	}
}
