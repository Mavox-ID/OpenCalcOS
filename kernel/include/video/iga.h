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
#ifndef _IGA1682_H
#define _IGA1682_H 1

#define IGA_ATTR_CTL			0x3C0
#define   IGA_IDX_VGA_OVERSCAN		0x11
#define DAC_W_INDEX                     0x03C8
#define DAC_DATA                        0x03C9
#define IGA_EXT_CNTRL                   0x3CE
#define   IGA_IDX_EXT_BUS_CNTL          0x30
#define     MEM_SIZE_ALIAS              0x3
#define     MEM_SIZE_1M                 0x0
#define     MEM_SIZE_2M                 0x1
#define     MEM_SIZE_4M                 0x2
#define     MEM_SIZE_RESERVED           0x3
#define   IGA_IDX_OVERSCAN_COLOR        0x58
#define   IGA_IDX_EXT_MEM_2             0x72

#endif /* !(_IGA1682_H) */
