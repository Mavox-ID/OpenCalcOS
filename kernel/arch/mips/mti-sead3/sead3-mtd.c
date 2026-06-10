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
#include <beep/init.h>
#include <beep/platform_device.h>
#include <beep/mtd/physmap.h>

static struct mtd_partition sead3_mtd_partitions[] = {
	{
		.name =		"User FS",
		.offset =	0x00000000,
		.size =		0x01fc0000,
	}, {
		.name =		"Board Config",
		.offset =	0x01fc0000,
		.size =		0x00040000,
		.mask_flags =	MTD_WRITEABLE
	},
};

static struct physmap_flash_data sead3_flash_data = {
	.width		= 4,
	.nr_parts	= ARRAY_SIZE(sead3_mtd_partitions),
	.parts		= sead3_mtd_partitions
};

static struct resource sead3_flash_resource = {
	.start		= 0x1c000000,
	.end		= 0x1dffffff,
	.flags		= IORESOURCE_MEM
};

static struct platform_device sead3_flash = {
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= {
		.platform_data	= &sead3_flash_data,
	},
	.num_resources	= 1,
	.resource	= &sead3_flash_resource,
};

static int __init sead3_mtd_init(void)
{
	platform_device_register(&sead3_flash);

	return 0;
}

module_init(sead3_mtd_init)
