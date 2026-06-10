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
#ifndef _ORINOCO_PCI_H
#define _ORINOCO_PCI_H

#include <beep/netdevice.h>

/* Driver specific data */
struct orinoco_pci_card {
	void __iomem *bridge_io;
	void __iomem *attr_io;
};

#ifdef CONFIG_PM
static int orinoco_pci_suspend(struct pci_dev *pdev, pm_message_t state)
{
	struct orinoco_private *priv = pci_get_drvdata(pdev);

	orinoco_down(priv);
	free_irq(pdev->irq, priv);
	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_set_power_state(pdev, PCI_D3hot);

	return 0;
}

static int orinoco_pci_resume(struct pci_dev *pdev)
{
	struct orinoco_private *priv = pci_get_drvdata(pdev);
	struct net_device *dev = priv->ndev;
	int err;

	pci_set_power_state(pdev, 0);
	err = pci_enable_device(pdev);
	if (err) {
		printk(KERN_ERR "%s: pci_enable_device failed on resume\n",
		       dev->name);
		return err;
	}
	pci_restore_state(pdev);

	err = request_irq(pdev->irq, orinoco_interrupt, IRQF_SHARED,
			  dev->name, priv);
	if (err) {
		printk(KERN_ERR "%s: cannot re-allocate IRQ on resume\n",
		       dev->name);
		pci_disable_device(pdev);
		return -EBUSY;
	}

	err = orinoco_up(priv);

	return err;
}
#else
#define orinoco_pci_suspend NULL
#define orinoco_pci_resume NULL
#endif

#endif /* _ORINOCO_PCI_H */
