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
#ifndef __RS100D_H__
#define __RS100D_H__

/* Registers */
#define R_00015C_NB_TOM                              0x00015C
#define   S_00015C_MC_FB_START(x)                      (((x) & 0xFFFF) << 0)
#define   G_00015C_MC_FB_START(x)                      (((x) >> 0) & 0xFFFF)
#define   C_00015C_MC_FB_START                         0xFFFF0000
#define   S_00015C_MC_FB_TOP(x)                        (((x) & 0xFFFF) << 16)
#define   G_00015C_MC_FB_TOP(x)                        (((x) >> 16) & 0xFFFF)
#define   C_00015C_MC_FB_TOP                           0x0000FFFF

#endif
