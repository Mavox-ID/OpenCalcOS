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
#ifndef __RADEON_BLIT_COMMON_H__

#define DI_PT_RECTLIST        0x11
#define DI_INDEX_SIZE_16_BIT  0x0
#define DI_SRC_SEL_AUTO_INDEX 0x2

#define FMT_8                 0x1
#define FMT_5_6_5             0x8
#define FMT_8_8_8_8           0x1a
#define COLOR_8               0x1
#define COLOR_5_6_5           0x8
#define COLOR_8_8_8_8         0x1a

#define RECT_UNIT_H           32
#define RECT_UNIT_W           (RADEON_GPU_PAGE_SIZE / 4 / RECT_UNIT_H)

#define __RADEON_BLIT_COMMON_H__
#endif
