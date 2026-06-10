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
#include <beep/module.h>
#include <beep/io.h>

unsigned long sh_io_port_base __read_mostly = -1;
EXPORT_SYMBOL(sh_io_port_base);

void __iomem *__ioport_map(unsigned long addr, unsigned int size)
{
	if (sh_mv.mv_ioport_map)
		return sh_mv.mv_ioport_map(addr, size);

	return (void __iomem *)(addr + sh_io_port_base);
}
EXPORT_SYMBOL(__ioport_map);

void __iomem *ioport_map(unsigned long port, unsigned int nr)
{
	void __iomem *ret;

	ret = __ioport_map_trapped(port, nr);
	if (ret)
		return ret;

	return __ioport_map(port, nr);
}
EXPORT_SYMBOL(ioport_map);

void ioport_unmap(void __iomem *addr)
{
	if (sh_mv.mv_ioport_unmap)
		sh_mv.mv_ioport_unmap(addr);
}
EXPORT_SYMBOL(ioport_unmap);
