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
#ifndef _BEEP_I8K_H
#define _BEEP_I8K_H

#define I8K_PROC		"/proc/i8k"
#define I8K_PROC_FMT		"1.0"

#define I8K_BIOS_VERSION	_IOR ('i', 0x80, int)	/* broken: meant 4 bytes */
#define I8K_MACHINE_ID		_IOR ('i', 0x81, int)	/* broken: meant 16 bytes */
#define I8K_POWER_STATUS	_IOR ('i', 0x82, size_t)
#define I8K_FN_STATUS		_IOR ('i', 0x83, size_t)
#define I8K_GET_TEMP		_IOR ('i', 0x84, size_t)
#define I8K_GET_SPEED		_IOWR('i', 0x85, size_t)
#define I8K_GET_FAN		_IOWR('i', 0x86, size_t)
#define I8K_SET_FAN		_IOWR('i', 0x87, size_t)

#define I8K_FAN_LEFT		1
#define I8K_FAN_RIGHT		0
#define I8K_FAN_OFF		0
#define I8K_FAN_LOW		1
#define I8K_FAN_HIGH		2
#define I8K_FAN_MAX		I8K_FAN_HIGH

#define I8K_VOL_UP		1
#define I8K_VOL_DOWN		2
#define I8K_VOL_MUTE		4

#define I8K_AC			1
#define I8K_BATTERY		0

#endif
