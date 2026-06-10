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
#ifndef __STMP_DEVICE_H__
#define __STMP_DEVICE_H__

#define STMP_OFFSET_REG_SET	0x4
#define STMP_OFFSET_REG_CLR	0x8
#define STMP_OFFSET_REG_TOG	0xc

extern int stmp_reset_block(void __iomem *);
#endif /* __STMP_DEVICE_H__ */
