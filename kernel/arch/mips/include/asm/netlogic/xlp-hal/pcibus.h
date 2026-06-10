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
#ifndef __NLM_HAL_PCIBUS_H__
#define	__NLM_HAL_PCIBUS_H__

/* PCIE Memory and IO regions */
#define	PCIE_MEM_BASE			0xd0000000ULL
#define	PCIE_MEM_LIMIT			0xdfffffffULL
#define	PCIE_IO_BASE			0x14000000ULL
#define	PCIE_IO_LIMIT			0x15ffffffULL

#define	PCIE_BRIDGE_CMD			0x1
#define	PCIE_BRIDGE_MSI_CAP		0x14
#define	PCIE_BRIDGE_MSI_ADDRL		0x15
#define	PCIE_BRIDGE_MSI_ADDRH		0x16
#define	PCIE_BRIDGE_MSI_DATA		0x17

/* XLP Global PCIE configuration space registers */
#define	PCIE_BYTE_SWAP_MEM_BASE		0x247
#define	PCIE_BYTE_SWAP_MEM_LIM		0x248
#define	PCIE_BYTE_SWAP_IO_BASE		0x249
#define	PCIE_BYTE_SWAP_IO_LIM		0x24A
#define	PCIE_MSI_STATUS			0x25A
#define	PCIE_MSI_EN			0x25B
#define	PCIE_INT_EN0			0x261

/* PCIE_MSI_EN */
#define	PCIE_MSI_VECTOR_INT_EN		0xFFFFFFFF

/* PCIE_INT_EN0 */
#define	PCIE_MSI_INT_EN			(1 << 9)

#ifndef __ASSEMBLY__

#define	nlm_read_pcie_reg(b, r)		nlm_read_reg(b, r)
#define	nlm_write_pcie_reg(b, r, v)	nlm_write_reg(b, r, v)
#define	nlm_get_pcie_base(node, inst)	\
			nlm_pcicfg_base(XLP_IO_PCIE_OFFSET(node, inst))
#define	nlm_get_pcie_regbase(node, inst)	\
			(nlm_get_pcie_base(node, inst) + XLP_IO_PCI_HDRSZ)

int xlp_pcie_link_irt(int link);
#endif
#endif /* __NLM_HAL_PCIBUS_H__ */
