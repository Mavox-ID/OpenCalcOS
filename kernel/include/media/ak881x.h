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
#ifndef AK881X_H
#define AK881X_H

#define AK881X_IF_MODE_MASK	(3 << 0)
#define AK881X_IF_MODE_BT656	(0 << 0)
#define AK881X_IF_MODE_MASTER	(1 << 0)
#define AK881X_IF_MODE_SLAVE	(2 << 0)
#define AK881X_FIELD		(1 << 2)
#define AK881X_COMPONENT	(1 << 3)

struct ak881x_pdata {
	unsigned long flags;
};

#endif
