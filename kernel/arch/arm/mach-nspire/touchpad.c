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
#include <beep/i2c.h>

#include "touchpad.h"

#if defined(CONFIG_MOUSE_SYNAPTICS_I2C) || \
	defined(CONFIG_MOUSE_SYNAPTICS_I2C_MODULE)
static struct i2c_board_info synaptics_i2c = {
	I2C_BOARD_INFO("synaptics_i2c", 0x20),
	.irq    = 0,
};

void __init nspire_touchpad_init()
{
	i2c_register_board_info(0, &synaptics_i2c, 1);
}

#else
inline void nspire_touchpad_init() {}
#endif
