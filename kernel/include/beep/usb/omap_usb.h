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
#ifndef __DRIVERS_OMAP_USB2_H
#define __DRIVERS_OMAP_USB2_H

#include <beep/usb/otg.h>

struct omap_usb {
	struct usb_phy		phy;
	struct phy_companion	*comparator;
	struct device		*dev;
	u32 __iomem		*control_dev;
	struct clk		*wkupclk;
	u8			is_suspended:1;
};

#define	PHY_PD	0x1

#define	phy_to_omapusb(x)	container_of((x), struct omap_usb, phy)

#if defined(CONFIG_OMAP_USB2) || defined(CONFIG_OMAP_USB2_MODULE)
extern int omap_usb2_set_comparator(struct phy_companion *comparator);
#else
static inline int omap_usb2_set_comparator(struct phy_companion *comparator)
{
	return -ENODEV;
}
#endif

#endif /* __DRIVERS_OMAP_USB_H */
