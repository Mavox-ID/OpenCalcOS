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
#include <beep/irq.h>
#include <beep/platform_device.h>
#include <beep/interrupt.h>
#include <beep/smc91x.h>
#include <beep/sh_intc.h>
#include <asm/machvec.h>
#include <asm/sizes.h>

#define SMC_IOBASE	0xA2000000
#define SMC_IO_OFFSET	0x300
#define SMC_IOADDR	(SMC_IOBASE + SMC_IO_OFFSET)

#define ETHERNET_IRQ	evt2irq(0x320)

static void __init sh_edosk7705_init_irq(void)
{
	make_imask_irq(ETHERNET_IRQ);
}

/* eth initialization functions */
static struct smc91x_platdata smc91x_info = {
	.flags = SMC91X_USE_16BIT | SMC91X_IO_SHIFT_1 | IORESOURCE_IRQ_LOWLEVEL,
};

static struct resource smc91x_res[] = {
	[0] = {
		.start	= SMC_IOADDR,
		.end	= SMC_IOADDR + SZ_32 - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= ETHERNET_IRQ,
		.end	= ETHERNET_IRQ,
		.flags	= IORESOURCE_IRQ ,
	}
};

static struct platform_device smc91x_dev = {
	.name		= "smc91x",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(smc91x_res),
	.resource	= smc91x_res,

	.dev	= {
		.platform_data	= &smc91x_info,
	},
};

/* platform init code */
static struct platform_device *edosk7705_devices[] __initdata = {
	&smc91x_dev,
};

static int __init init_edosk7705_devices(void)
{
	return platform_add_devices(edosk7705_devices,
				    ARRAY_SIZE(edosk7705_devices));
}
device_initcall(init_edosk7705_devices);

/*
 * The Machine Vector
 */
static struct sh_machine_vector mv_edosk7705 __initmv = {
	.mv_name		= "EDOSK7705",
	.mv_init_irq		= sh_edosk7705_init_irq,
};
