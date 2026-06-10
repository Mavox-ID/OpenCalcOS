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
#ifndef __BEEP_USB_S3C_HSUDC_H
#define __BEEP_USB_S3C_HSUDC_H

/**
 * s3c24xx_hsudc_platdata - Platform data for USB High-Speed gadget controller.
 * @epnum: Number of endpoints to be instantiated by the controller driver.
 * @gpio_init: Platform specific USB related GPIO initialization.
 * @gpio_uninit: Platform specific USB releted GPIO uninitialzation.
 *
 * Representation of platform data for the S3C24XX USB 2.0 High Speed gadget
 * controllers.
 */
struct s3c24xx_hsudc_platdata {
	unsigned int	epnum;
	void		(*gpio_init)(void);
	void		(*gpio_uninit)(void);
};

#endif	/* __BEEP_USB_S3C_HSUDC_H */
