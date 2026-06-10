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
#ifndef __WSP_MSI_H
#define __WSP_MSI_H

#ifdef CONFIG_PCI_MSI
extern void wsp_setup_phb_msi(struct pci_controller *phb);
#else
static inline void wsp_setup_phb_msi(struct pci_controller *phb) { }
#endif

#endif /* __WSP_MSI_H */
