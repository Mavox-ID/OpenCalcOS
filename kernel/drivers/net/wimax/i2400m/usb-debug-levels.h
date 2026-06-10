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
#ifndef __debug_levels__h__
#define __debug_levels__h__

/* Maximum compile and run time debug level for all submodules */
#define D_MODULENAME i2400m_usb
#define D_MASTER CONFIG_WIMAX_I2400M_DEBUG_LEVEL

#include <beep/wimax/debug.h>

/* List of all the enabled modules */
enum d_module {
	D_SUBMODULE_DECLARE(usb),
	D_SUBMODULE_DECLARE(fw),
	D_SUBMODULE_DECLARE(notif),
	D_SUBMODULE_DECLARE(rx),
	D_SUBMODULE_DECLARE(tx),
};


#endif /* #ifndef __debug_levels__h__ */
