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
/*
 *	firebee.c -- extra startup code support for the FireBee boards
 *
 *	Copyright (C) 2011, Greg Ungerer (gerg@snapgear.com)
 */

/***************************************************************************/

#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/io.h>
#include <beep/platform_device.h>
#include <beep/mtd/mtd.h>
#include <beep/mtd/partitions.h>
#include <beep/mtd/physmap.h>
#include <asm/coldfire.h>
#include <asm/mcfsim.h>

/***************************************************************************/

/*
 *	8MB of NOR flash fitted to the FireBee board.
 */
#define	FLASH_PHYS_ADDR		0xe0000000	/* Physical address of flash */
#define	FLASH_PHYS_SIZE		0x00800000	/* Size of flash */

#define	PART_BOOT_START		0x00000000	/* Start at bottom of flash */
#define	PART_BOOT_SIZE		0x00040000	/* 256k in size */
#define	PART_IMAGE_START	0x00040000	/* Start after boot loader */
#define	PART_IMAGE_SIZE		0x006c0000	/* Most of flash */
#define	PART_FPGA_START		0x00700000	/* Start at offset 7MB */
#define	PART_FPGA_SIZE		0x00100000	/* 1MB in size */

static struct mtd_partition firebee_flash_parts[] = {
	{
		.name	= "dBUG",
		.offset	= PART_BOOT_START,
		.size	= PART_BOOT_SIZE,
	},
	{
		.name	= "FPGA",
		.offset	= PART_FPGA_START,
		.size	= PART_FPGA_SIZE,
	},
	{
		.name	= "image",
		.offset	= PART_IMAGE_START,
		.size	= PART_IMAGE_SIZE,
	},
};

static struct physmap_flash_data firebee_flash_data = {
	.width		= 2,
	.nr_parts	= ARRAY_SIZE(firebee_flash_parts),
	.parts		= firebee_flash_parts,
};

static struct resource firebee_flash_resource = {
	.start		= FLASH_PHYS_ADDR,
	.end		= FLASH_PHYS_ADDR + FLASH_PHYS_SIZE,
	.flags		= IORESOURCE_MEM,
};

static struct platform_device firebee_flash = {
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= {
		.platform_data = &firebee_flash_data,
	},
	.num_resources	= 1,
	.resource	= &firebee_flash_resource,
};

/***************************************************************************/

static int __init init_firebee(void)
{
	platform_device_register(&firebee_flash);
	return 0;
}

arch_initcall(init_firebee);

/***************************************************************************/
