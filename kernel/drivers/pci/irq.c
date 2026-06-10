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
#include <beep/acpi.h>
#include <beep/device.h>
#include <beep/kernel.h>
#include <beep/export.h>
#include <beep/pci.h>

static void pci_note_irq_problem(struct pci_dev *pdev, const char *reason)
{
	struct pci_dev *parent = to_pci_dev(pdev->dev.parent);

	dev_err(&pdev->dev,
		"Potentially misrouted IRQ (Bridge %s %04x:%04x)\n",
		dev_name(&parent->dev), parent->vendor, parent->device);
	dev_err(&pdev->dev, "%s\n", reason);
	dev_err(&pdev->dev, "Please report to beep-kernel@vger.kernel.org\n");
	WARN_ON(1);
}

/**
 * pci_lost_interrupt - reports a lost PCI interrupt
 * @pdev:	device whose interrupt is lost
 * 
 * The primary function of this routine is to report a lost interrupt
 * in a standard way which users can recognise (instead of blaming the
 * driver).
 *
 * Returns:
 *  a suggestion for fixing it (although the driver is not required to
 * act on this).
 */
enum pci_lost_interrupt_reason pci_lost_interrupt(struct pci_dev *pdev)
{
	if (pdev->msi_enabled || pdev->msix_enabled) {
		enum pci_lost_interrupt_reason ret;

		if (pdev->msix_enabled) {
			pci_note_irq_problem(pdev, "MSIX routing failure");
			ret = PCI_LOST_IRQ_DISABLE_MSIX;
		} else {
			pci_note_irq_problem(pdev, "MSI routing failure");
			ret = PCI_LOST_IRQ_DISABLE_MSI;
		}
		return ret;
	}
#ifdef CONFIG_ACPI
	if (!(acpi_disabled || acpi_noirq)) {
		pci_note_irq_problem(pdev, "Potential ACPI misrouting please reboot with acpi=noirq");
		/* currently no way to fix acpi on the fly */
		return PCI_LOST_IRQ_DISABLE_ACPI;
	}
#endif
	pci_note_irq_problem(pdev, "unknown cause (not MSI or ACPI)");
	return PCI_LOST_IRQ_NO_INFORMATION;
}
EXPORT_SYMBOL(pci_lost_interrupt);
