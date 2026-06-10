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
#ifndef __MACH_AT91_MATRIX_H__
#define __MACH_AT91_MATRIX_H__

#ifndef __ASSEMBLY__
extern void __iomem *at91_matrix_base;

#define at91_matrix_read(field) \
	__raw_readl(at91_matrix_base + field)

#define at91_matrix_write(field, value) \
	__raw_writel(value, at91_matrix_base + field);

#else
.extern at91_matrix_base
#endif

#endif /* __MACH_AT91_MATRIX_H__ */
