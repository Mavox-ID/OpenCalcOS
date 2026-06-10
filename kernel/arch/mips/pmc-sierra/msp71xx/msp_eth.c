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
#include <beep/kernel.h>
#include <beep/ioport.h>
#include <beep/platform_device.h>
#include <beep/delay.h>
#include <msp_regs.h>
#include <msp_int.h>
#include <msp_gpio_macros.h>


#define MSP_ETHERNET_GPIO0	14
#define MSP_ETHERNET_GPIO1	15
#define MSP_ETHERNET_GPIO2	16

#ifdef CONFIG_MSP_HAS_TSMAC
#define MSP_TSMAC_SIZE	0x10020
#define MSP_TSMAC_ID	"pmc_tsmac"

static struct resource msp_tsmac0_resources[] = {
	[0] = {
		.start	= MSP_MAC0_BASE,
		.end	= MSP_MAC0_BASE + MSP_TSMAC_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= MSP_INT_MAC0,
		.end	= MSP_INT_MAC0,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct resource msp_tsmac1_resources[] = {
	[0] = {
		.start	= MSP_MAC1_BASE,
		.end	= MSP_MAC1_BASE + MSP_TSMAC_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= MSP_INT_MAC1,
		.end	= MSP_INT_MAC1,
		.flags	= IORESOURCE_IRQ,
	},
};
static struct resource msp_tsmac2_resources[] = {
	[0] = {
		.start	= MSP_MAC2_BASE,
		.end	= MSP_MAC2_BASE + MSP_TSMAC_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= MSP_INT_SAR,
		.end	= MSP_INT_SAR,
		.flags	= IORESOURCE_IRQ,
	},
};


static struct platform_device tsmac_device[] = {
	[0] = {
		.name	= MSP_TSMAC_ID,
		.id	= 0,
		.num_resources = ARRAY_SIZE(msp_tsmac0_resources),
		.resource = msp_tsmac0_resources,
	},
	[1] = {
		.name	= MSP_TSMAC_ID,
		.id	= 1,
		.num_resources = ARRAY_SIZE(msp_tsmac1_resources),
		.resource = msp_tsmac1_resources,
	},
	[2] = {
		.name	= MSP_TSMAC_ID,
		.id	= 2,
		.num_resources = ARRAY_SIZE(msp_tsmac2_resources),
		.resource = msp_tsmac2_resources,
	},
};
#define msp_eth_devs	tsmac_device

#else
/* If it is not TSMAC assume MSP_ETH (100Mbps) */
#define MSP_ETH_ID	"pmc_mspeth"
#define MSP_ETH_SIZE	0xE0
static struct resource msp_eth0_resources[] = {
	[0] = {
		.start	= MSP_MAC0_BASE,
		.end	= MSP_MAC0_BASE + MSP_ETH_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= MSP_INT_MAC0,
		.end	= MSP_INT_MAC0,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct resource msp_eth1_resources[] = {
	[0] = {
		.start	= MSP_MAC1_BASE,
		.end	= MSP_MAC1_BASE + MSP_ETH_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= MSP_INT_MAC1,
		.end	= MSP_INT_MAC1,
		.flags	= IORESOURCE_IRQ,
	},
};



static struct platform_device mspeth_device[] = {
	[0] = {
		.name	= MSP_ETH_ID,
		.id	= 0,
		.num_resources = ARRAY_SIZE(msp_eth0_resources),
		.resource = msp_eth0_resources,
	},
	[1] = {
		.name	= MSP_ETH_ID,
		.id	= 1,
		.num_resources = ARRAY_SIZE(msp_eth1_resources),
		.resource = msp_eth1_resources,
	},

};
#define msp_eth_devs	mspeth_device

#endif
int __init msp_eth_setup(void)
{
	int i, ret = 0;

	/* Configure the GPIO and take the ethernet PHY out of reset */
	msp_gpio_pin_mode(MSP_GPIO_OUTPUT, MSP_ETHERNET_GPIO0);
	msp_gpio_pin_hi(MSP_ETHERNET_GPIO0);

#ifdef CONFIG_MSP_HAS_TSMAC
	/* 3 phys on boards with TSMAC */
	msp_gpio_pin_mode(MSP_GPIO_OUTPUT, MSP_ETHERNET_GPIO1);
	msp_gpio_pin_hi(MSP_ETHERNET_GPIO1);

	msp_gpio_pin_mode(MSP_GPIO_OUTPUT, MSP_ETHERNET_GPIO2);
	msp_gpio_pin_hi(MSP_ETHERNET_GPIO2);
#endif
	for (i = 0; i < ARRAY_SIZE(msp_eth_devs); i++) {
		ret = platform_device_register(&msp_eth_devs[i]);
		printk(KERN_INFO "device: %d, return value = %d\n", i, ret);
		if (ret) {
			platform_device_unregister(&msp_eth_devs[i]);
			break;
		}
	}

	if (ret)
		printk(KERN_WARNING "Could not initialize "
						"MSPETH device structures.\n");

	return ret;
}
subsys_initcall(msp_eth_setup);
