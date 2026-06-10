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
#if defined(CONFIG_USB_STORAGE_REALTEK) || \
		defined(CONFIG_USB_STORAGE_REALTEK_MODULE)

UNUSUAL_DEV(0x0bda, 0x0138, 0x0000, 0x9999,
		"Realtek",
		"USB Card Reader",
		USB_SC_DEVICE, USB_PR_DEVICE, init_realtek_cr, 0),

UNUSUAL_DEV(0x0bda, 0x0158, 0x0000, 0x9999,
		"Realtek",
		"USB Card Reader",
		USB_SC_DEVICE, USB_PR_DEVICE, init_realtek_cr, 0),

UNUSUAL_DEV(0x0bda, 0x0159, 0x0000, 0x9999,
		"Realtek",
		"USB Card Reader",
		USB_SC_DEVICE, USB_PR_DEVICE, init_realtek_cr, 0),

#endif  /* defined(CONFIG_USB_STORAGE_REALTEK) || ... */
