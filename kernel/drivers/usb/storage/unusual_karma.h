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
#if defined(CONFIG_USB_STORAGE_KARMA) || \
		defined(CONFIG_USB_STORAGE_KARMA_MODULE)

UNUSUAL_DEV(  0x045a, 0x5210, 0x0101, 0x0101,
		"Rio",
		"Rio Karma",
		USB_SC_SCSI, USB_PR_KARMA, rio_karma_init, 0),

#endif /* defined(CONFIG_USB_STORAGE_KARMA) || ... */
