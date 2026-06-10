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
/**
 * Interface definitions for the USB host driver.
 */

#ifndef _SYS_HV_DRV_USB_HOST_INTF_H
#define _SYS_HV_DRV_USB_HOST_INTF_H

#include <arch/usb_host.h>


/** Offset for the EHCI register MMIO region. */
#define HV_USB_HOST_MMIO_OFFSET_EHCI ((uint64_t) USB_HOST_HCCAPBASE_REG)

/** Offset for the OHCI register MMIO region. */
#define HV_USB_HOST_MMIO_OFFSET_OHCI ((uint64_t) USB_HOST_OHCD_HC_REVISION_REG)

/** Size of the register MMIO region.  This turns out to be the same for
 *  both EHCI and OHCI. */
#define HV_USB_HOST_MMIO_SIZE ((uint64_t) 0x1000)

/** The number of service domains supported by the USB host shim. */
#define HV_USB_HOST_NUM_SVC_DOM 1


#endif /* _SYS_HV_DRV_USB_HOST_INTF_H */
