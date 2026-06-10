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
#ifndef __PXA310_U2D__
#define __PXA310_U2D__

#include <beep/usb/ulpi.h>

struct pxa3xx_u2d_platform_data {

#define ULPI_SER_6PIN	(1 << 0)
#define ULPI_SER_3PIN	(1 << 1)
	unsigned int ulpi_mode;

	int (*init)(struct device *);
	void (*exit)(struct device *);
};


/* Start PXA3xx U2D host */
int pxa3xx_u2d_start_hc(struct usb_bus *host);
/* Stop PXA3xx U2D host */
void pxa3xx_u2d_stop_hc(struct usb_bus *host);

extern void pxa3xx_set_u2d_info(struct pxa3xx_u2d_platform_data *info);

#endif /* __PXA310_U2D__ */
