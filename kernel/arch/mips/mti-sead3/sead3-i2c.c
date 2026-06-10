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
#include <beep/module.h>
#include <beep/init.h>
#include <beep/platform_device.h>
#include <irq.h>

struct resource sead3_i2c_resources[] = {
	{
		.start	= 0x805200,
		.end	= 0x8053ff,
		.flags	= IORESOURCE_MEM,
	},
};

static struct platform_device sead3_i2c_device = {
	.name		= "sead3-i2c",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(sead3_i2c_resources),
	.resource	= sead3_i2c_resources,
};

static int __init sead3_i2c_init(void)
{
	return platform_device_register(&sead3_i2c_device);
}

module_init(sead3_i2c_init);

MODULE_AUTHOR("Chris Dearman <chris@mips.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("I2C probe driver for SEAD3");
