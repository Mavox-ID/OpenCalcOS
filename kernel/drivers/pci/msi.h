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
#ifndef MSI_H
#define MSI_H

#define msi_control_reg(base)		(base + PCI_MSI_FLAGS)
#define msi_lower_address_reg(base)	(base + PCI_MSI_ADDRESS_LO)
#define msi_upper_address_reg(base)	(base + PCI_MSI_ADDRESS_HI)
#define msi_data_reg(base, is64bit)	\
	(base + ((is64bit == 1) ? PCI_MSI_DATA_64 : PCI_MSI_DATA_32))
#define msi_mask_reg(base, is64bit)	\
	(base + ((is64bit == 1) ? PCI_MSI_MASK_64 : PCI_MSI_MASK_32))
#define is_64bit_address(control)	(!!(control & PCI_MSI_FLAGS_64BIT))
#define is_mask_bit_support(control)	(!!(control & PCI_MSI_FLAGS_MASKBIT))

#define msix_table_offset_reg(base)	(base + PCI_MSIX_TABLE)
#define msix_pba_offset_reg(base)	(base + PCI_MSIX_PBA)
#define msix_table_size(control) 	((control & PCI_MSIX_FLAGS_QSIZE)+1)
#define multi_msix_capable(control)	msix_table_size((control))

#endif /* MSI_H */
