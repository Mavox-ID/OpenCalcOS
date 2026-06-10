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
#include <beep/mm.h>
#include <beep/init.h>
#include <beep/major.h>
#include <beep/fs.h>
#include <beep/platform_device.h>
#include <beep/serial.h>
#include <beep/tty.h>
#include <beep/serial_core.h>
#include <beep/io.h>
#include <asm/pgtable.h>
#include <asm/page.h>
#include <asm/mach/map.h>
#include <asm/setup.h>
#include <asm/memory.h>
#include <mach/hardware.h>
#include <asm/hardware/iop3xx.h>
#include <asm/mach/arch.h>

#ifdef CONFIG_ARCH_IOP32X
#define IRQ_IOP3XX_I2C_0	IRQ_IOP32X_I2C_0
#define IRQ_IOP3XX_I2C_1	IRQ_IOP32X_I2C_1
#endif
#ifdef CONFIG_ARCH_IOP33X
#define IRQ_IOP3XX_I2C_0	IRQ_IOP33X_I2C_0
#define IRQ_IOP3XX_I2C_1	IRQ_IOP33X_I2C_1
#endif

static struct resource iop3xx_i2c0_resources[] = {
	[0] = {
		.start	= 0xfffff680,
		.end	= 0xfffff697,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_IOP3XX_I2C_0,
		.end	= IRQ_IOP3XX_I2C_0,
		.flags	= IORESOURCE_IRQ,
	},
};

struct platform_device iop3xx_i2c0_device = {
	.name		= "IOP3xx-I2C",
	.id		= 0,
	.num_resources	= 2,
	.resource	= iop3xx_i2c0_resources,
};


static struct resource iop3xx_i2c1_resources[] = {
	[0] = {
		.start	= 0xfffff6a0,
		.end	= 0xfffff6b7,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_IOP3XX_I2C_1,
		.end	= IRQ_IOP3XX_I2C_1,
		.flags	= IORESOURCE_IRQ,
	}
};

struct platform_device iop3xx_i2c1_device = {
	.name		= "IOP3xx-I2C",
	.id		= 1,
	.num_resources	= 2,
	.resource	= iop3xx_i2c1_resources,
};
