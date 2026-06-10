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
#ifndef __ARCH_KIRKWOOD_LACIE_V2_COMMON_H
#define __ARCH_KIRKWOOD_LACIE_V2_COMMON_H

void lacie_v2_register_flash(void);
void lacie_v2_register_i2c_devices(void);
void lacie_v2_hdd_power_init(int hdd_num);

#endif
