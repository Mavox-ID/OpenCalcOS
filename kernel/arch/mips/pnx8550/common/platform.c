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
#include <beep/device.h>
#include <beep/dma-mapping.h>
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/resource.h>
#include <beep/serial.h>
#include <beep/serial_pnx8xxx.h>
#include <beep/platform_device.h>
#include <beep/usb/ohci_pdriver.h>

#include <int.h>
#include <usb.h>
#include <uart.h>

static struct resource pnx8550_usb_ohci_resources[] = {
	[0] = {
		.start		= PNX8550_USB_OHCI_OP_BASE,
		.end		= PNX8550_USB_OHCI_OP_BASE +
				  PNX8550_USB_OHCI_OP_LEN,
		.flags		= IORESOURCE_MEM,
	},
	[1] = {
		.start		= PNX8550_INT_USB,
		.end		= PNX8550_INT_USB,
		.flags		= IORESOURCE_IRQ,
	},
};

static struct resource pnx8550_uart_resources[] = {
	[0] = {
		.start		= PNX8550_UART_PORT0,
		.end		= PNX8550_UART_PORT0 + 0xfff,
		.flags		= IORESOURCE_MEM,
	},
	[1] = {
		.start		= PNX8550_UART_INT(0),
		.end		= PNX8550_UART_INT(0),
		.flags		= IORESOURCE_IRQ,
	},
	[2] = {
		.start		= PNX8550_UART_PORT1,
		.end		= PNX8550_UART_PORT1 + 0xfff,
		.flags		= IORESOURCE_MEM,
	},
	[3] = {
		.start		= PNX8550_UART_INT(1),
		.end		= PNX8550_UART_INT(1),
		.flags		= IORESOURCE_IRQ,
	},
};

struct pnx8xxx_port pnx8xxx_ports[] = {
	[0] = {
		.port   = {
			.type		= PORT_PNX8XXX,
			.iotype		= UPIO_MEM,
			.membase	= (void __iomem *)PNX8550_UART_PORT0,
			.mapbase	= PNX8550_UART_PORT0,
			.irq		= PNX8550_UART_INT(0),
			.uartclk	= 3692300,
			.fifosize	= 16,
			.flags		= UPF_BOOT_AUTOCONF,
			.line		= 0,
		},
	},
	[1] = {
		.port   = {
			.type		= PORT_PNX8XXX,
			.iotype		= UPIO_MEM,
			.membase	= (void __iomem *)PNX8550_UART_PORT1,
			.mapbase	= PNX8550_UART_PORT1,
			.irq		= PNX8550_UART_INT(1),
			.uartclk	= 3692300,
			.fifosize	= 16,
			.flags		= UPF_BOOT_AUTOCONF,
			.line		= 1,
		},
	},
};

/* The dmamask must be set for OHCI to work */
static u64 ohci_dmamask = DMA_BIT_MASK(32);

static u64 uart_dmamask = DMA_BIT_MASK(32);

static int pnx8550_usb_ohci_power_on(struct platform_device *pdev)
{
	/*
	 * Set register CLK48CTL to enable and 48MHz
	 */
	outl(0x00000003, PCI_BASE | 0x0004770c);

	/*
	 * Set register CLK12CTL to enable and 48MHz
	 */
	outl(0x00000003, PCI_BASE | 0x00047710);

	udelay(100);

	return 0;
}

static void pnx8550_usb_ohci_power_off(struct platform_device *pdev)
{
	udelay(10);
}

static struct usb_ohci_pdata pnx8550_usb_ohci_pdata = {
	.power_on	= pnx8550_usb_ohci_power_on,
	.power_off	= pnx8550_usb_ohci_power_off,
};

static struct platform_device pnx8550_usb_ohci_device = {
	.name		= "ohci-platform",
	.id		= -1,
	.dev = {
		.dma_mask		= &ohci_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platform_data		= &pnx8550_usb_ohci_pdata,
	},
	.num_resources	= ARRAY_SIZE(pnx8550_usb_ohci_resources),
	.resource	= pnx8550_usb_ohci_resources,
};

static struct platform_device pnx8550_uart_device = {
	.name		= "pnx8xxx-uart",
	.id		= -1,
	.dev = {
		.dma_mask		= &uart_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platform_data = pnx8xxx_ports,
	},
	.num_resources	= ARRAY_SIZE(pnx8550_uart_resources),
	.resource	= pnx8550_uart_resources,
};

static struct platform_device *pnx8550_platform_devices[] __initdata = {
	&pnx8550_usb_ohci_device,
	&pnx8550_uart_device,
};

static int __init pnx8550_platform_init(void)
{
	return platform_add_devices(pnx8550_platform_devices,
			            ARRAY_SIZE(pnx8550_platform_devices));
}

arch_initcall(pnx8550_platform_init);
