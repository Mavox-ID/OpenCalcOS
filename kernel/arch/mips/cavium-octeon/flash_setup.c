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
#include <beep/export.h>
#include <beep/mtd/mtd.h>
#include <beep/mtd/map.h>
#include <beep/mtd/partitions.h>

#include <asm/octeon/octeon.h>

static struct map_info flash_map;
static struct mtd_info *mymtd;
static const char *part_probe_types[] = {
	"cmdlinepart",
#ifdef CONFIG_MTD_REDBOOT_PARTS
	"RedBoot",
#endif
	NULL
};

/**
 * Module/ driver initialization.
 *
 * Returns Zero on success
 */
static int __init flash_init(void)
{
	/*
	 * Read the bootbus region 0 setup to determine the base
	 * address of the flash.
	 */
	union cvmx_mio_boot_reg_cfgx region_cfg;
	region_cfg.u64 = cvmx_read_csr(CVMX_MIO_BOOT_REG_CFGX(0));
	if (region_cfg.s.en) {
		/*
		 * The bootloader always takes the flash and sets its
		 * address so the entire flash fits below
		 * 0x1fc00000. This way the flash aliases to
		 * 0x1fc00000 for booting. Software can access the
		 * full flash at the true address, while core boot can
		 * access 4MB.
		 */
		/* Use this name so old part lines work */
		flash_map.name = "phys_mapped_flash";
		flash_map.phys = region_cfg.s.base << 16;
		flash_map.size = 0x1fc00000 - flash_map.phys;
		/* 8-bit bus (0 + 1) or 16-bit bus (1 + 1) */
		flash_map.bankwidth = region_cfg.s.width + 1;
		flash_map.virt = ioremap(flash_map.phys, flash_map.size);
		pr_notice("Bootbus flash: Setting flash for %luMB flash at "
			  "0x%08llx\n", flash_map.size >> 20, flash_map.phys);
		simple_map_init(&flash_map);
		mymtd = do_map_probe("cfi_probe", &flash_map);
		if (mymtd) {
			mymtd->owner = THIS_MODULE;
			mtd_device_parse_register(mymtd, part_probe_types,
						  NULL, NULL, 0);
		} else {
			pr_err("Failed to register MTD device for flash\n");
		}
	}
	return 0;
}

late_initcall(flash_init);
