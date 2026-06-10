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
#include "devices-common.h"

struct platform_device *__init mxc_register_gpio(char *name, int id,
	resource_size_t iobase, resource_size_t iosize, int irq, int irq_high)
{
	struct resource res[] = {
		{
			.start = iobase,
			.end = iobase + iosize - 1,
			.flags = IORESOURCE_MEM,
		}, {
			.start = irq,
			.end = irq,
			.flags = IORESOURCE_IRQ,
		}, {
			.start = irq_high,
			.end = irq_high,
			.flags = IORESOURCE_IRQ,
		},
	};

	return platform_device_register_resndata(&mxc_aips_bus,
			name, id, res, ARRAY_SIZE(res), NULL, 0);
}
