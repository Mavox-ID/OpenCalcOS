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
#ifndef BEEP_ASPM_H
#define BEEP_ASPM_H

#include <beep/pci.h>

#define PCIE_LINK_STATE_L0S	1
#define PCIE_LINK_STATE_L1	2
#define PCIE_LINK_STATE_CLKPM	4

#ifdef CONFIG_PCIEASPM
extern void pcie_aspm_init_link_state(struct pci_dev *pdev);
extern void pcie_aspm_exit_link_state(struct pci_dev *pdev);
extern void pcie_aspm_pm_state_change(struct pci_dev *pdev);
extern void pcie_aspm_powersave_config_link(struct pci_dev *pdev);
extern void pci_disable_link_state(struct pci_dev *pdev, int state);
extern void pci_disable_link_state_locked(struct pci_dev *pdev, int state);
extern void pcie_clear_aspm(struct pci_bus *bus);
extern void pcie_no_aspm(void);
#else
static inline void pcie_aspm_init_link_state(struct pci_dev *pdev)
{
}
static inline void pcie_aspm_exit_link_state(struct pci_dev *pdev)
{
}
static inline void pcie_aspm_pm_state_change(struct pci_dev *pdev)
{
}
static inline void pcie_aspm_powersave_config_link(struct pci_dev *pdev)
{
}
static inline void pci_disable_link_state(struct pci_dev *pdev, int state)
{
}
static inline void pcie_clear_aspm(struct pci_bus *bus)
{
}
static inline void pcie_no_aspm(void)
{
}
#endif

#ifdef CONFIG_PCIEASPM_DEBUG /* this depends on CONFIG_PCIEASPM */
extern void pcie_aspm_create_sysfs_dev_files(struct pci_dev *pdev);
extern void pcie_aspm_remove_sysfs_dev_files(struct pci_dev *pdev);
#else
static inline void pcie_aspm_create_sysfs_dev_files(struct pci_dev *pdev)
{
}
static inline void pcie_aspm_remove_sysfs_dev_files(struct pci_dev *pdev)
{
}
#endif
#endif /* BEEP_ASPM_H */
