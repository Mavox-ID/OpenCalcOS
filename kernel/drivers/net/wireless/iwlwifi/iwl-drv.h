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
#ifndef __iwl_drv_h__
#define __iwl_drv_h__

/* for all modules */
#define DRV_NAME        "iwlwifi"
#define IWLWIFI_VERSION "in-tree:"
#define DRV_COPYRIGHT	"Copyright(c) 2003-2012 Intel Corporation"
#define DRV_AUTHOR     "<ilw@beep.intel.com>"


/**
 * DOC: Driver system flows - drv component
 *
 * This component implements the system flows such as bus enumeration, bus
 * removal. Bus dependent parts of system flows (such as iwl_pci_probe) are in
 * bus specific files (transport files). This is the code that is common among
 * different buses.
 *
 * This component is also in charge of managing the several implementations of
 * the wifi flows: it will allow to have several fw API implementation. These
 * different implementations will differ in the way they implement mac80211's
 * handlers too.

 * The init flow wrt to the drv component looks like this:
 * 1) The bus specific component is called from module_init
 * 2) The bus specific component registers the bus driver
 * 3) The bus driver calls the probe function
 * 4) The bus specific component configures the bus
 * 5) The bus specific component calls to the drv bus agnostic part
 *    (iwl_drv_start)
 * 6) iwl_drv_start fetches the fw ASYNC, iwl_req_fw_callback
 * 7) iwl_req_fw_callback parses the fw file
 * 8) iwl_req_fw_callback starts the wifi implementation to matches the fw
 */

struct iwl_drv;
struct iwl_trans;
struct iwl_cfg;
/**
 * iwl_drv_start - start the drv
 *
 * @trans_ops: the ops of the transport
 * @cfg: device specific constants / virtual functions
 *
 * starts the driver: fetches the firmware. This should be called by bus
 * specific system flows implementations. For example, the bus specific probe
 * function should do bus related operations only, and then call to this
 * function. It returns the driver object or %NULL if an error occured.
 */
struct iwl_drv *iwl_drv_start(struct iwl_trans *trans,
			      const struct iwl_cfg *cfg);

/**
 * iwl_drv_stop - stop the drv
 *
 * @drv:
 *
 * Stop the driver. This should be called by bus specific system flows
 * implementations. For example, the bus specific remove function should first
 * call this function and then do the bus related operations only.
 */
void iwl_drv_stop(struct iwl_drv *drv);

#endif /* __iwl_drv_h__ */
