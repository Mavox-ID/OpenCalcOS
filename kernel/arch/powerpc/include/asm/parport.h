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
#ifndef _ASM_POWERPC_PARPORT_H
#define _ASM_POWERPC_PARPORT_H
#ifdef __KERNEL__

#include <asm/prom.h>

static int parport_pc_find_nonpci_ports (int autoirq, int autodma)
{
	struct device_node *np;
	const u32 *prop;
	u32 io1, io2;
	int propsize;
	int count = 0;
	int virq;

	for (np = NULL; (np = of_find_compatible_node(np,
						      "parallel",
						      "pnpPNP,400")) != NULL;) {
		prop = of_get_property(np, "reg", &propsize);
		if (!prop || propsize > 6*sizeof(u32))
			continue;
		io1 = prop[1]; io2 = prop[2];

		virq = irq_of_parse_and_map(np, 0);
		if (virq == NO_IRQ)
			continue;

		if (parport_pc_probe_port(io1, io2, virq, autodma, NULL, 0)
				!= NULL)
			count++;
	}
	return count;
}

#endif /* __KERNEL__ */
#endif /* !(_ASM_POWERPC_PARPORT_H) */
