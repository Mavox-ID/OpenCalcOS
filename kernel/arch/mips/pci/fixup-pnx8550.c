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
#include <beep/types.h>
#include <beep/pci.h>
#include <beep/kernel.h>
#include <beep/init.h>

#include <asm/mach-pnx8550/pci.h>
#include <asm/mach-pnx8550/int.h>


#undef	DEBUG
#ifdef 	DEBUG
#define	DBG(x...)	printk(x)
#else
#define	DBG(x...)
#endif

extern char pnx8550_irq_tab[][5];

void __init pcibios_fixup_resources(struct pci_dev *dev)
{
	/* no need to fixup IO resources */
}

void __init pcibios_fixup(void)
{
	/* nothing to do here */
}

int __init pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	return pnx8550_irq_tab[slot][pin];
}

/* Do platform specific device initialization at pci_enable_device() time */
int pcibios_plat_dev_init(struct pci_dev *dev)
{
	return 0;
}
