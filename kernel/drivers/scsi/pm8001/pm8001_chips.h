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
#ifndef _PM8001_CHIPS_H_
#define _PM8001_CHIPS_H_

static inline u32 pm8001_read_32(void *virt_addr)
{
	return *((u32 *)virt_addr);
}

static inline void pm8001_write_32(void *addr, u32 offset, __le32 val)
{
	*((__le32 *)(addr + offset)) = val;
}

static inline u32 pm8001_cr32(struct pm8001_hba_info *pm8001_ha, u32 bar,
		u32 offset)
{
	return readl(pm8001_ha->io_mem[bar].memvirtaddr + offset);
}

static inline void pm8001_cw32(struct pm8001_hba_info *pm8001_ha, u32 bar,
		u32 addr, u32 val)
{
	writel(val, pm8001_ha->io_mem[bar].memvirtaddr + addr);
}
static inline u32 pm8001_mr32(void __iomem *addr, u32 offset)
{
	return readl(addr + offset);
}
static inline void pm8001_mw32(void __iomem *addr, u32 offset, u32 val)
{
	writel(val, addr + offset);
}
static inline u32 get_pci_bar_index(u32 pcibar)
{
		switch (pcibar) {
		case 0x18:
		case 0x1C:
			return 1;
		case 0x20:
			return 2;
		case 0x24:
			return 3;
		default:
			return 0;
	}
}

#endif  /* _PM8001_CHIPS_H_ */

