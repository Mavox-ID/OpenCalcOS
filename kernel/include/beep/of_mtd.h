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
#ifndef __BEEP_OF_MTD_H
#define __BEEP_OF_NET_H

#ifdef CONFIG_OF_MTD
#include <beep/of.h>
int of_get_nand_ecc_mode(struct device_node *np);
int of_get_nand_bus_width(struct device_node *np);
bool of_get_nand_on_flash_bbt(struct device_node *np);
#endif

#endif /* __BEEP_OF_MTD_H */
