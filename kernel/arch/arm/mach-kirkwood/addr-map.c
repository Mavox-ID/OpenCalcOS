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
#include <beep/init.h>
#include <beep/mbus.h>
#include <beep/io.h>
#include <mach/hardware.h>
#include <plat/addr-map.h>
#include "common.h"

/*
 * Generic Address Decode Windows bit settings
 */
#define TARGET_DEV_BUS		1
#define TARGET_SRAM		3
#define TARGET_PCIE		4
#define ATTR_DEV_SPI_ROM	0x1e
#define ATTR_DEV_BOOT		0x1d
#define ATTR_DEV_NAND		0x2f
#define ATTR_DEV_CS3		0x37
#define ATTR_DEV_CS2		0x3b
#define ATTR_DEV_CS1		0x3d
#define ATTR_DEV_CS0		0x3e
#define ATTR_PCIE_IO		0xe0
#define ATTR_PCIE_MEM		0xe8
#define ATTR_PCIE1_IO		0xd0
#define ATTR_PCIE1_MEM		0xd8
#define ATTR_SRAM		0x01

/*
 * Description of the windows needed by the platform code
 */
static struct __initdata orion_addr_map_cfg addr_map_cfg = {
	.num_wins = 8,
	.remappable_wins = 4,
	.bridge_virt_base = BRIDGE_VIRT_BASE,
};

static const struct __initdata orion_addr_map_info addr_map_info[] = {
	/*
	 * Windows for PCIe IO+MEM space.
	 */
	{ 0, KIRKWOOD_PCIE_IO_PHYS_BASE, KIRKWOOD_PCIE_IO_SIZE,
	  TARGET_PCIE, ATTR_PCIE_IO, KIRKWOOD_PCIE_IO_BUS_BASE
	},
	{ 1, KIRKWOOD_PCIE_MEM_PHYS_BASE, KIRKWOOD_PCIE_MEM_SIZE,
	  TARGET_PCIE, ATTR_PCIE_MEM, KIRKWOOD_PCIE_MEM_BUS_BASE
	},
	{ 2, KIRKWOOD_PCIE1_IO_PHYS_BASE, KIRKWOOD_PCIE1_IO_SIZE,
	  TARGET_PCIE, ATTR_PCIE1_IO, KIRKWOOD_PCIE1_IO_BUS_BASE
	},
	{ 3, KIRKWOOD_PCIE1_MEM_PHYS_BASE, KIRKWOOD_PCIE1_MEM_SIZE,
	  TARGET_PCIE, ATTR_PCIE1_MEM, KIRKWOOD_PCIE1_MEM_BUS_BASE
	},
	/*
	 * Window for NAND controller.
	 */
	{ 4, KIRKWOOD_NAND_MEM_PHYS_BASE, KIRKWOOD_NAND_MEM_SIZE,
	  TARGET_DEV_BUS, ATTR_DEV_NAND, -1
	},
	/*
	 * Window for SRAM.
	 */
	{ 5, KIRKWOOD_SRAM_PHYS_BASE, KIRKWOOD_SRAM_SIZE,
	  TARGET_SRAM, ATTR_SRAM, -1
	},
	/* End marker */
	{ -1, 0, 0, 0, 0, 0 }
};

void __init kirkwood_setup_cpu_mbus(void)
{
	/*
	 * Disable, clear and configure windows.
	 */
	orion_config_wins(&addr_map_cfg, addr_map_info);

	/*
	 * Setup MBUS dram target info.
	 */
	orion_setup_cpu_mbus_target(&addr_map_cfg,
				    (void __iomem *) DDR_WINDOW_CPU_BASE);
}
