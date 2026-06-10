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
#ifndef PXA2XX_UDC_H
#define PXA2XX_UDC_H

struct pxa2xx_udc_mach_info {
        int  (*udc_is_connected)(void);		/* do we see host? */
        void (*udc_command)(int cmd);
#define	PXA2XX_UDC_CMD_CONNECT		0	/* let host see us */
#define	PXA2XX_UDC_CMD_DISCONNECT	1	/* so host won't see us */

	/* Boards following the design guidelines in the developer's manual,
	 * with on-chip GPIOs not Lubbock's weird hardware, can have a sane
	 * VBUS IRQ and omit the methods above.  Store the GPIO number
	 * here.  Note that sometimes the signals go through inverters...
	 */
	bool	gpio_pullup_inverted;
	int	gpio_pullup;			/* high == pullup activated */
};

#endif
