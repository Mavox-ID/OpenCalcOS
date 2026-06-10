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
#ifndef __RV200D_H__
#define __RV200D_H__

#define R_00015C_AGP_BASE_2                          0x00015C
#define   S_00015C_AGP_BASE_ADDR_2(x)                  (((x) & 0xF) << 0)
#define   G_00015C_AGP_BASE_ADDR_2(x)                  (((x) >> 0) & 0xF)
#define   C_00015C_AGP_BASE_ADDR_2                     0xFFFFFFF0

#endif
