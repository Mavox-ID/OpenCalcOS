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
#ifndef __BEEP_USB_USBA_H
#define __BEEP_USB_USBA_H

struct usba_ep_data {
	char	*name;
	int	index;
	int	fifo_size;
	int	nr_banks;
	int	can_dma;
	int	can_isoc;
};

struct usba_platform_data {
	int			vbus_pin;
	int			vbus_pin_inverted;
	int			num_ep;
	struct usba_ep_data	ep[0];
};

#endif /* __BEEP_USB_USBA_H */
