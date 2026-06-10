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
#define IO_CONCAT(a,b)	_IO_CONCAT(a,b)
#define _IO_CONCAT(a,b)	a ## _ ## b

#ifndef __IO_PREFIX
#error "Don't include this header without a valid system prefix"
#endif

void __iomem *IO_CONCAT(__IO_PREFIX,ioport_map)(unsigned long addr, unsigned int size);
void IO_CONCAT(__IO_PREFIX,ioport_unmap)(void __iomem *addr);
void IO_CONCAT(__IO_PREFIX,mem_init)(void);

#undef __IO_PREFIX
