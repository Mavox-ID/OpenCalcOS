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
#ifndef __MT9T112_H__
#define __MT9T112_H__

#define MT9T112_FLAG_PCLK_RISING_EDGE	(1 << 0)
#define MT9T112_FLAG_DATAWIDTH_8	(1 << 1) /* default width is 10 */

struct mt9t112_pll_divider {
	u8 m, n;
	u8 p1, p2, p3, p4, p5, p6, p7;
};

/*
 * mt9t112 camera info
 */
struct mt9t112_camera_info {
	u32 flags;
	struct mt9t112_pll_divider divider;
};

#endif /* __MT9T112_H__ */
