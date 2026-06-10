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
#ifndef __PLAT_PCIE_H
#define __PLAT_PCIE_H

struct pci_bus;

u32 orion_pcie_dev_id(void __iomem *base);
u32 orion_pcie_rev(void __iomem *base);
int orion_pcie_link_up(void __iomem *base);
int orion_pcie_x4_mode(void __iomem *base);
int orion_pcie_get_local_bus_nr(void __iomem *base);
void orion_pcie_set_local_bus_nr(void __iomem *base, int nr);
void orion_pcie_reset(void __iomem *base);
void orion_pcie_setup(void __iomem *base);
int orion_pcie_rd_conf(void __iomem *base, struct pci_bus *bus,
		       u32 devfn, int where, int size, u32 *val);
int orion_pcie_rd_conf_tlp(void __iomem *base, struct pci_bus *bus,
			   u32 devfn, int where, int size, u32 *val);
int orion_pcie_rd_conf_wa(void __iomem *wa_base, struct pci_bus *bus,
			  u32 devfn, int where, int size, u32 *val);
int orion_pcie_wr_conf(void __iomem *base, struct pci_bus *bus,
		       u32 devfn, int where, int size, u32 val);


#endif
