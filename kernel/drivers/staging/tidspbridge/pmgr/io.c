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

/*  ----------------------------------- Platform Manager */
#include <dspbridge/dev.h>

/*  ----------------------------------- This */
#include <ioobj.h>
#include <dspbridge/io.h>

/*
 *  ======== io_create ========
 *  Purpose:
 *      Create an IO manager object, responsible for managing IO between
 *      CHNL and msg_ctrl
 */
int io_create(struct io_mgr **io_man, struct dev_object *hdev_obj,
		     const struct io_attrs *mgr_attrts)
{
	struct bridge_drv_interface *intf_fxns;
	struct io_mgr *hio_mgr = NULL;
	struct io_mgr_ *pio_mgr = NULL;
	int status = 0;

	*io_man = NULL;

	/* A memory base of 0 implies no memory base: */
	if ((mgr_attrts->shm_base != 0) && (mgr_attrts->sm_length == 0))
		status = -EINVAL;

	if (mgr_attrts->word_size == 0)
		status = -EINVAL;

	if (!status) {
		dev_get_intf_fxns(hdev_obj, &intf_fxns);

		/* Let Bridge channel module finish the create: */
		status = (*intf_fxns->io_create) (&hio_mgr, hdev_obj,
						      mgr_attrts);

		if (!status) {
			pio_mgr = (struct io_mgr_ *)hio_mgr;
			pio_mgr->intf_fxns = intf_fxns;
			pio_mgr->dev_obj = hdev_obj;

			/* Return the new channel manager handle: */
			*io_man = hio_mgr;
		}
	}

	return status;
}

/*
 *  ======== io_destroy ========
 *  Purpose:
 *      Delete IO manager.
 */
int io_destroy(struct io_mgr *hio_mgr)
{
	struct bridge_drv_interface *intf_fxns;
	struct io_mgr_ *pio_mgr = (struct io_mgr_ *)hio_mgr;
	int status;

	intf_fxns = pio_mgr->intf_fxns;

	/* Let Bridge channel module destroy the io_mgr: */
	status = (*intf_fxns->io_destroy) (hio_mgr);

	return status;
}
