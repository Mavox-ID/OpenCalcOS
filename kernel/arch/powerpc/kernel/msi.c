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
#include <beep/kernel.h>
#include <beep/msi.h>
#include <beep/pci.h>

#include <asm/machdep.h>

int arch_msi_check_device(struct pci_dev* dev, int nvec, int type)
{
	if (!ppc_md.setup_msi_irqs || !ppc_md.teardown_msi_irqs) {
		pr_debug("msi: Platform doesn't provide MSI callbacks.\n");
		return -ENOSYS;
	}

	/* PowerPC doesn't support multiple MSI yet */
	if (type == PCI_CAP_ID_MSI && nvec > 1)
		return 1;

	if (ppc_md.msi_check_device) {
		pr_debug("msi: Using platform check routine.\n");
		return ppc_md.msi_check_device(dev, nvec, type);
	}

        return 0;
}

int arch_setup_msi_irqs(struct pci_dev *dev, int nvec, int type)
{
	return ppc_md.setup_msi_irqs(dev, nvec, type);
}

void arch_teardown_msi_irqs(struct pci_dev *dev)
{
	ppc_md.teardown_msi_irqs(dev);
}
