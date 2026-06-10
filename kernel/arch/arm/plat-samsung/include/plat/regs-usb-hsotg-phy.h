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
/* Note, this is a separate header file as some of the clock framework
 * needs to touch this if the clk_48m is used as the USB OHCI or other
 * peripheral source.
*/

#ifndef __PLAT_S3C64XX_REGS_USB_HSOTG_PHY_H
#define __PLAT_S3C64XX_REGS_USB_HSOTG_PHY_H __FILE__

/* S3C64XX_PA_USB_HSPHY */

#define S3C_HSOTG_PHYREG(x)	((x) + S3C_VA_USB_HSPHY)

#define S3C_PHYPWR				S3C_HSOTG_PHYREG(0x00)
#define S3C_PHYPWR_NORMAL_MASK			(0x19 << 0)
#define S3C_PHYPWR_OTG_DISABLE			(1 << 4)
#define S3C_PHYPWR_ANALOG_POWERDOWN		(1 << 3)
#define SRC_PHYPWR_FORCE_SUSPEND		(1 << 1)

#define S3C_PHYCLK				S3C_HSOTG_PHYREG(0x04)
#define S3C_PHYCLK_MODE_USB11			(1 << 6)
#define S3C_PHYCLK_EXT_OSC			(1 << 5)
#define S3C_PHYCLK_CLK_FORCE			(1 << 4)
#define S3C_PHYCLK_ID_PULL			(1 << 2)
#define S3C_PHYCLK_CLKSEL_MASK			(0x3 << 0)
#define S3C_PHYCLK_CLKSEL_SHIFT			(0)
#define S3C_PHYCLK_CLKSEL_48M			(0x0 << 0)
#define S3C_PHYCLK_CLKSEL_12M			(0x2 << 0)
#define S3C_PHYCLK_CLKSEL_24M			(0x3 << 0)

#define S3C_RSTCON				S3C_HSOTG_PHYREG(0x08)
#define S3C_RSTCON_PHYCLK			(1 << 2)
#define S3C_RSTCON_HCLK				(1 << 1)
#define S3C_RSTCON_PHY				(1 << 0)

#define S3C_PHYTUNE				S3C_HSOTG_PHYREG(0x20)

#endif /* __PLAT_S3C64XX_REGS_USB_HSOTG_PHY_H */
