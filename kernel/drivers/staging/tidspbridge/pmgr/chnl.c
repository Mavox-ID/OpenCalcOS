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

/*  ----------------------------------- OS Adaptation Layer */
#include <dspbridge/sync.h>

/*  ----------------------------------- Platform Manager */
#include <dspbridge/proc.h>
#include <dspbridge/dev.h>

/*  ----------------------------------- Others */
#include <dspbridge/chnlpriv.h>
#include <chnlobj.h>

/*  ----------------------------------- This */
#include <dspbridge/chnl.h>

/*
 *  ======== chnl_create ========
 *  Purpose:
 *      Create a channel manager object, responsible for opening new channels
 *      and closing old ones for a given 'Bridge board.
 */
int chnl_create(struct chnl_mgr **channel_mgr,
		       struct dev_object *hdev_obj,
		       const struct chnl_mgrattrs *mgr_attrts)
{
	int status;
	struct chnl_mgr *hchnl_mgr;
	struct chnl_mgr_ *chnl_mgr_obj = NULL;

	*channel_mgr = NULL;

	/* Validate args: */
	if ((0 < mgr_attrts->max_channels) &&
	    (mgr_attrts->max_channels <= CHNL_MAXCHANNELS))
		status = 0;
	else if (mgr_attrts->max_channels == 0)
		status = -EINVAL;
	else
		status = -ECHRNG;

	if (mgr_attrts->word_size == 0)
		status = -EINVAL;

	if (!status) {
		status = dev_get_chnl_mgr(hdev_obj, &hchnl_mgr);
		if (!status && hchnl_mgr != NULL)
			status = -EEXIST;

	}

	if (!status) {
		struct bridge_drv_interface *intf_fxns;
		dev_get_intf_fxns(hdev_obj, &intf_fxns);
		/* Let Bridge channel module finish the create: */
		status = (*intf_fxns->chnl_create) (&hchnl_mgr, hdev_obj,
							mgr_attrts);
		if (!status) {
			/* Fill in DSP API channel module's fields of the
			 * chnl_mgr structure */
			chnl_mgr_obj = (struct chnl_mgr_ *)hchnl_mgr;
			chnl_mgr_obj->intf_fxns = intf_fxns;
			/* Finally, return the new channel manager handle: */
			*channel_mgr = hchnl_mgr;
		}
	}

	return status;
}

/*
 *  ======== chnl_destroy ========
 *  Purpose:
 *      Close all open channels, and destroy the channel manager.
 */
int chnl_destroy(struct chnl_mgr *hchnl_mgr)
{
	struct chnl_mgr_ *chnl_mgr_obj = (struct chnl_mgr_ *)hchnl_mgr;
	struct bridge_drv_interface *intf_fxns;
	int status;

	if (chnl_mgr_obj) {
		intf_fxns = chnl_mgr_obj->intf_fxns;
		/* Let Bridge channel module destroy the chnl_mgr: */
		status = (*intf_fxns->chnl_destroy) (hchnl_mgr);
	} else {
		status = -EFAULT;
	}

	return status;
}
