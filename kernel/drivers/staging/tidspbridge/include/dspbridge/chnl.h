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
#ifndef CHNL_
#define CHNL_

#include <dspbridge/chnlpriv.h>

/*
 *  ======== chnl_create ========
 *  Purpose:
 *      Create a channel manager object, responsible for opening new channels
 *      and closing old ones for a given board.
 *  Parameters:
 *      channel_mgr:    Location to store a channel manager object on output.
 *      hdev_obj:     Handle to a device object.
 *      mgr_attrts:      Channel manager attributes.
 *      mgr_attrts->max_channels:   Max channels
 *      mgr_attrts->birq:        Channel's I/O IRQ number.
 *      mgr_attrts->irq_shared:     TRUE if the IRQ is shareable.
 *      mgr_attrts->word_size:   DSP Word size in equivalent PC bytes..
 *  Returns:
 *      0:                Success;
 *      -EFAULT:            hdev_obj is invalid.
 *      -EINVAL: max_channels is 0.
 *               Invalid DSP word size (must be > 0).
 *               Invalid base address for DSP communications.
 *      -ENOMEM:            Insufficient memory for requested resources.
 *      -EIO:             Unable to plug channel ISR for configured IRQ.
 *      -ECHRNG:     This manager cannot handle this many channels.
 *      -EEXIST:       Channel manager already exists for this device.
 *  Requires:
 *      channel_mgr != NULL.
 *      mgr_attrts != NULL.
 *  Ensures:
 *      0:                Subsequent calls to chnl_create() for the same
 *                              board without an intervening call to
 *                              chnl_destroy() will fail.
 */
extern int chnl_create(struct chnl_mgr **channel_mgr,
			      struct dev_object *hdev_obj,
			      const struct chnl_mgrattrs *mgr_attrts);

/*
 *  ======== chnl_destroy ========
 *  Purpose:
 *      Close all open channels, and destroy the channel manager.
 *  Parameters:
 *      hchnl_mgr:           Channel manager object.
 *  Returns:
 *      0:            Success.
 *      -EFAULT:        hchnl_mgr was invalid.
 *  Requires:
 *  Ensures:
 *      0:            Cancels I/O on each open channel.
 *                          Closes each open channel.
 *                          chnl_create may subsequently be called for the
 *                          same board.
 */
extern int chnl_destroy(struct chnl_mgr *hchnl_mgr);

#endif /* CHNL_ */
