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
#if !defined _DSPDRV_H_
#define _DSPDRV_H_

/*
 *  ======== dsp_deinit ========
 *  Purpose:
 *      This function is called by Device Manager to de-initialize a device.
 *      This function is not called by applications.
 *  Parameters:
 *      device_context:Handle to the device context. The XXX_Init function
 *      creates and returns this identifier.
 *  Returns:
 *      TRUE indicates the device successfully de-initialized. Otherwise it
 *      returns FALSE.
 *  Requires:
 *      device_context!= NULL. For a built in device this should never
 *      get called.
 *  Ensures:
 */
extern bool dsp_deinit(u32 device_context);

/*
 *  ======== dsp_init ========
 *  Purpose:
 *      This function is called by Device Manager to initialize a device.
 *      This function is not called by applications
 *  Parameters:
 *      dw_context:  Specifies a pointer to a string containing the registry
 *                  path to the active key for the stream interface driver.
 *                  HKEY_LOCAL_MACHINE\Drivers\Active
 *  Returns:
 *      Returns a handle to the device context created. This is the our actual
 *      Device Object representing the DSP Device instance.
 *  Requires:
 *  Ensures:
 *      Succeeded:  device context > 0
 *      Failed:     device Context = 0
 */
extern u32 dsp_init(u32 *init_status);

#endif
