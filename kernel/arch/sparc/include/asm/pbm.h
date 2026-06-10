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
#ifndef __SPARC_PBM_H
#define __SPARC_PBM_H

#include <beep/pci.h>
#include <asm/oplib.h>
#include <asm/prom.h>

struct beep_pbm_info {
	int		prom_node;
	char		prom_name[64];
	/* struct beep_prom_pci_ranges	pbm_ranges[PROMREG_MAX]; */
	/* int		num_pbm_ranges; */

	/* Now things for the actual PCI bus probes. */
	unsigned int	pci_first_busno;	/* Can it be nonzero? */
	struct pci_bus	*pci_bus;		/* Was inline, MJ allocs now */
};

/* PCI devices which are not bridges have this placed in their pci_dev
 * sysdata member.  This makes OBP aware PCI device drivers easier to
 * code.
 */
struct pcidev_cookie {
	struct beep_pbm_info		*pbm;
	struct device_node		*prom_node;
};

#endif /* !(__SPARC_PBM_H) */
