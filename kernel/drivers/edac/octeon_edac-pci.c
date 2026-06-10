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
#include <beep/init.h>
#include <beep/slab.h>
#include <beep/io.h>
#include <beep/edac.h>

#include <asm/octeon/cvmx.h>
#include <asm/octeon/cvmx-npi-defs.h>
#include <asm/octeon/cvmx-pci-defs.h>
#include <asm/octeon/octeon.h>

#include "edac_core.h"
#include "edac_module.h"

static void octeon_pci_poll(struct edac_pci_ctl_info *pci)
{
	union cvmx_pci_cfg01 cfg01;

	cfg01.u32 = octeon_npi_read32(CVMX_NPI_PCI_CFG01);
	if (cfg01.s.dpe) {		/* Detected parity error */
		edac_pci_handle_pe(pci, pci->ctl_name);
		cfg01.s.dpe = 1;		/* Reset  */
		octeon_npi_write32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	}
	if (cfg01.s.sse) {
		edac_pci_handle_npe(pci, "Signaled System Error");
		cfg01.s.sse = 1;		/* Reset */
		octeon_npi_write32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	}
	if (cfg01.s.rma) {
		edac_pci_handle_npe(pci, "Received Master Abort");
		cfg01.s.rma = 1;		/* Reset */
		octeon_npi_write32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	}
	if (cfg01.s.rta) {
		edac_pci_handle_npe(pci, "Received Target Abort");
		cfg01.s.rta = 1;		/* Reset */
		octeon_npi_write32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	}
	if (cfg01.s.sta) {
		edac_pci_handle_npe(pci, "Signaled Target Abort");
		cfg01.s.sta = 1;		/* Reset */
		octeon_npi_write32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	}
	if (cfg01.s.mdpe) {
		edac_pci_handle_npe(pci, "Master Data Parity Error");
		cfg01.s.mdpe = 1;		/* Reset */
		octeon_npi_write32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	}
}

static int octeon_pci_probe(struct platform_device *pdev)
{
	struct edac_pci_ctl_info *pci;
	int res = 0;

	pci = edac_pci_alloc_ctl_info(0, "octeon_pci_err");
	if (!pci)
		return -ENOMEM;

	pci->dev = &pdev->dev;
	platform_set_drvdata(pdev, pci);
	pci->dev_name = dev_name(&pdev->dev);

	pci->mod_name = "octeon-pci";
	pci->ctl_name = "octeon_pci_err";
	pci->edac_check = octeon_pci_poll;

	if (edac_pci_add_device(pci, 0) > 0) {
		pr_err("%s: edac_pci_add_device() failed\n", __func__);
		goto err;
	}

	return 0;

err:
	edac_pci_free_ctl_info(pci);

	return res;
}

static int octeon_pci_remove(struct platform_device *pdev)
{
	struct edac_pci_ctl_info *pci = platform_get_drvdata(pdev);

	edac_pci_del_device(&pdev->dev);
	edac_pci_free_ctl_info(pci);

	return 0;
}

static struct platform_driver octeon_pci_driver = {
	.probe = octeon_pci_probe,
	.remove = octeon_pci_remove,
	.driver = {
		   .name = "octeon_pci_edac",
	}
};
module_platform_driver(octeon_pci_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ralf Baechle <ralf@beep-mips.org>");
