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
#include <beep/leds.h>
#include <beep/platform_device.h>

#define LEDFLAGS(bits, shift)		\
	((bits << 8) | (shift << 8))

#define LEDBITS(id, shift, bits)	\
	.name = id #shift,		\
	.flags = LEDFLAGS(bits, shift)

struct led_info led_data_info[] = {
	{ LEDBITS("bit", 0, 1) },
	{ LEDBITS("bit", 1, 1) },
	{ LEDBITS("bit", 2, 1) },
	{ LEDBITS("bit", 3, 1) },
	{ LEDBITS("bit", 4, 1) },
	{ LEDBITS("bit", 5, 1) },
	{ LEDBITS("bit", 6, 1) },
	{ LEDBITS("bit", 7, 1) },
	{ LEDBITS("all", 0, 8) },
};

static struct led_platform_data led_data = {
	.num_leds	= ARRAY_SIZE(led_data_info),
	.leds		= led_data_info
};

static struct resource pled_resources[] = {
	{
		.start	= 0x1f000210,
		.end	= 0x1f000217,
		.flags	= IORESOURCE_MEM
	}
};

static struct platform_device pled_device = {
	.name			= "sead3::pled",
	.id			= 0,
	.dev			= {
		.platform_data	= &led_data,
	},
	.num_resources		= ARRAY_SIZE(pled_resources),
	.resource		= pled_resources
};


static struct resource fled_resources[] = {
	{
		.start			= 0x1f000218,
		.end			= 0x1f00021f,
		.flags			= IORESOURCE_MEM
	}
};

static struct platform_device fled_device = {
	.name			= "sead3::fled",
	.id			= 0,
	.dev			= {
		.platform_data	= &led_data,
	},
	.num_resources		= ARRAY_SIZE(fled_resources),
	.resource		= fled_resources
};

static int __init led_init(void)
{
	platform_device_register(&pled_device);
	return platform_device_register(&fled_device);
}

module_init(led_init);

MODULE_AUTHOR("Chris Dearman <chris@mips.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LED probe driver for SEAD-3");
