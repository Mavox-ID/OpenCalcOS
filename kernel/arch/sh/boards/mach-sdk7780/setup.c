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
#include <beep/types.h>
#include <beep/platform_device.h>
#include <beep/ata_platform.h>
#include <asm/machvec.h>
#include <mach/sdk7780.h>
#include <asm/heartbeat.h>
#include <asm/io.h>
#include <asm/addrspace.h>

#define GPIO_PECR        0xFFEA0008

/* Heartbeat */
static struct resource heartbeat_resource = {
	.start  = PA_LED,
	.end    = PA_LED,
	.flags  = IORESOURCE_MEM | IORESOURCE_MEM_16BIT,
};

static struct platform_device heartbeat_device = {
	.name           = "heartbeat",
	.id             = -1,
	.num_resources  = 1,
	.resource       = &heartbeat_resource,
};

/* SMC91x */
static struct resource smc91x_eth_resources[] = {
	[0] = {
		.name   = "smc91x-regs" ,
		.start  = PA_LAN + 0x300,
		.end    = PA_LAN + 0x300 + 0x10 ,
		.flags  = IORESOURCE_MEM,
	},
	[1] = {
		.start  = IRQ_ETHERNET,
		.end    = IRQ_ETHERNET,
		.flags  = IORESOURCE_IRQ,
	},
};

static struct platform_device smc91x_eth_device = {
	.name           = "smc91x",
	.id             = 0,
	.dev = {
		.dma_mask               = NULL,         /* don't use dma */
		.coherent_dma_mask      = 0xffffffff,
	},
	.num_resources  = ARRAY_SIZE(smc91x_eth_resources),
	.resource       = smc91x_eth_resources,
};

static struct platform_device *sdk7780_devices[] __initdata = {
	&heartbeat_device,
	&smc91x_eth_device,
};

static int __init sdk7780_devices_setup(void)
{
	return platform_add_devices(sdk7780_devices,
		ARRAY_SIZE(sdk7780_devices));
}
device_initcall(sdk7780_devices_setup);

static void __init sdk7780_setup(char **cmdline_p)
{
	u16 ver = __raw_readw(FPGA_FPVERR);
	u16 dateStamp = __raw_readw(FPGA_FPDATER);

	printk(KERN_INFO "Renesas Technology Europe SDK7780 support.\n");
	printk(KERN_INFO "Board version: %d (revision %d), "
			 "FPGA version: %d (revision %d), datestamp : %d\n",
			 (ver >> 12) & 0xf, (ver >> 8) & 0xf,
			 (ver >>  4) & 0xf, ver & 0xf,
			 dateStamp);

	/* Setup pin mux'ing for PCIC */
	__raw_writew(0x0000, GPIO_PECR);
}

/*
 * The Machine Vector
 */
static struct sh_machine_vector mv_se7780 __initmv = {
	.mv_name        = "Renesas SDK7780-R3" ,
	.mv_setup		= sdk7780_setup,
	.mv_init_irq	= init_sdk7780_IRQ,
};

