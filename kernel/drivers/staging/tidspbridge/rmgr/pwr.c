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
/*  ----------------------------------- Host OS */
#include <dspbridge/host_os.h>

/*  ----------------------------------- This */
#include <dspbridge/pwr.h>

/*  ----------------------------------- Resource Manager */
#include <dspbridge/devdefs.h>
#include <dspbridge/drv.h>

/*  ----------------------------------- Platform Manager */
#include <dspbridge/dev.h>

/*  ----------------------------------- Link Driver */
#include <dspbridge/dspioctl.h>

/*
 *  ======== pwr_sleep_dsp ========
 *    Send command to DSP to enter sleep state.
 */
int pwr_sleep_dsp(const u32 sleep_code, const u32 timeout)
{
	struct bridge_drv_interface *intf_fxns;
	struct bridge_dev_context *dw_context;
	int status = -EPERM;
	struct dev_object *hdev_obj = NULL;
	u32 ioctlcode = 0;
	u32 arg = timeout;

	for (hdev_obj = (struct dev_object *)drv_get_first_dev_object();
	     hdev_obj != NULL;
	     hdev_obj =
	     (struct dev_object *)drv_get_next_dev_object((u32) hdev_obj)) {
		if (dev_get_bridge_context(hdev_obj,
						(struct bridge_dev_context **)
						   &dw_context)) {
			continue;
		}
		if (dev_get_intf_fxns(hdev_obj,
						(struct bridge_drv_interface **)
						&intf_fxns)) {
			continue;
		}
		if (sleep_code == PWR_DEEPSLEEP)
			ioctlcode = BRDIOCTL_DEEPSLEEP;
		else if (sleep_code == PWR_EMERGENCYDEEPSLEEP)
			ioctlcode = BRDIOCTL_EMERGENCYSLEEP;
		else
			status = -EINVAL;

		if (status != -EINVAL) {
			status = (*intf_fxns->dev_cntrl) (dw_context,
							      ioctlcode,
							      (void *)&arg);
		}
	}
	return status;
}

/*
 *  ======== pwr_wake_dsp ========
 *    Send command to DSP to wake it from sleep.
 */
int pwr_wake_dsp(const u32 timeout)
{
	struct bridge_drv_interface *intf_fxns;
	struct bridge_dev_context *dw_context;
	int status = -EPERM;
	struct dev_object *hdev_obj = NULL;
	u32 arg = timeout;

	for (hdev_obj = (struct dev_object *)drv_get_first_dev_object();
	     hdev_obj != NULL;
	     hdev_obj = (struct dev_object *)drv_get_next_dev_object
	     ((u32) hdev_obj)) {
		if (!(dev_get_bridge_context(hdev_obj,
						      (struct bridge_dev_context
						       **)&dw_context))) {
			if (!(dev_get_intf_fxns(hdev_obj,
			      (struct bridge_drv_interface **)&intf_fxns))) {
				status =
				    (*intf_fxns->dev_cntrl) (dw_context,
							BRDIOCTL_WAKEUP,
							(void *)&arg);
			}
		}
	}
	return status;
}

/*
 *  ======== pwr_pm_pre_scale========
 *    Sends pre-notification message to DSP.
 */
int pwr_pm_pre_scale(u16 voltage_domain, u32 level)
{
	struct bridge_drv_interface *intf_fxns;
	struct bridge_dev_context *dw_context;
	int status = -EPERM;
	struct dev_object *hdev_obj = NULL;
	u32 arg[2];

	arg[0] = voltage_domain;
	arg[1] = level;

	for (hdev_obj = (struct dev_object *)drv_get_first_dev_object();
	     hdev_obj != NULL;
	     hdev_obj = (struct dev_object *)drv_get_next_dev_object
	     ((u32) hdev_obj)) {
		if (!(dev_get_bridge_context(hdev_obj,
						      (struct bridge_dev_context
						       **)&dw_context))) {
			if (!(dev_get_intf_fxns(hdev_obj,
			      (struct bridge_drv_interface **)&intf_fxns))) {
				status =
				    (*intf_fxns->dev_cntrl) (dw_context,
						BRDIOCTL_PRESCALE_NOTIFY,
						(void *)&arg);
			}
		}
	}
	return status;
}

/*
 *  ======== pwr_pm_post_scale========
 *    Sends post-notification message to DSP.
 */
int pwr_pm_post_scale(u16 voltage_domain, u32 level)
{
	struct bridge_drv_interface *intf_fxns;
	struct bridge_dev_context *dw_context;
	int status = -EPERM;
	struct dev_object *hdev_obj = NULL;
	u32 arg[2];

	arg[0] = voltage_domain;
	arg[1] = level;

	for (hdev_obj = (struct dev_object *)drv_get_first_dev_object();
	     hdev_obj != NULL;
	     hdev_obj = (struct dev_object *)drv_get_next_dev_object
	     ((u32) hdev_obj)) {
		if (!(dev_get_bridge_context(hdev_obj,
						      (struct bridge_dev_context
						       **)&dw_context))) {
			if (!(dev_get_intf_fxns(hdev_obj,
			      (struct bridge_drv_interface **)&intf_fxns))) {
				status =
				    (*intf_fxns->dev_cntrl) (dw_context,
						BRDIOCTL_POSTSCALE_NOTIFY,
						(void *)&arg);
			}
		}
	}
	return status;

}
