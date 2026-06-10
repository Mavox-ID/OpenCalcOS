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
#ifndef MACH_U300_I2C_H
#define MACH_U300_I2C_H

#ifdef CONFIG_I2C_STU300
void __init u300_i2c_register_board_devices(void);
#else
/* Compile out this stuff if no I2C adapter is available */
static inline void __init u300_i2c_register_board_devices(void)
{
}
#endif

#endif
