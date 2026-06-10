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
#include <beep/init.h>
#include <beep/platform_device.h>
#include <beep/serial_8250.h>
#include <beep/clk.h>
#include <beep/err.h>

#include <asm/mach-ath79/ath79.h>
#include <asm/mach-ath79/ar71xx_regs.h>
#include <asm/mach-ath79/ar933x_uart_platform.h>
#include "common.h"
#include "dev-common.h"

static struct resource ath79_uart_resources[] = {
	{
		.start	= AR71XX_UART_BASE,
		.end	= AR71XX_UART_BASE + AR71XX_UART_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
};

#define AR71XX_UART_FLAGS (UPF_BOOT_AUTOCONF | UPF_SKIP_TEST | UPF_IOREMAP)
static struct plat_serial8250_port ath79_uart_data[] = {
	{
		.mapbase	= AR71XX_UART_BASE,
		.irq		= ATH79_MISC_IRQ_UART,
		.flags		= AR71XX_UART_FLAGS,
		.iotype		= UPIO_MEM32,
		.regshift	= 2,
	}, {
		/* terminating entry */
	}
};

static struct platform_device ath79_uart_device = {
	.name		= "serial8250",
	.id		= PLAT8250_DEV_PLATFORM,
	.resource	= ath79_uart_resources,
	.num_resources	= ARRAY_SIZE(ath79_uart_resources),
	.dev = {
		.platform_data	= ath79_uart_data
	},
};

static struct resource ar933x_uart_resources[] = {
	{
		.start	= AR933X_UART_BASE,
		.end	= AR933X_UART_BASE + AR71XX_UART_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= ATH79_MISC_IRQ_UART,
		.end	= ATH79_MISC_IRQ_UART,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct ar933x_uart_platform_data ar933x_uart_data;
static struct platform_device ar933x_uart_device = {
	.name		= "ar933x-uart",
	.id		= -1,
	.resource	= ar933x_uart_resources,
	.num_resources	= ARRAY_SIZE(ar933x_uart_resources),
	.dev = {
		.platform_data	= &ar933x_uart_data,
	},
};

void __init ath79_register_uart(void)
{
	struct clk *clk;

	clk = clk_get(NULL, "uart");
	if (IS_ERR(clk))
		panic("unable to get UART clock, err=%ld", PTR_ERR(clk));

	if (soc_is_ar71xx() ||
	    soc_is_ar724x() ||
	    soc_is_ar913x() ||
	    soc_is_ar934x()) {
		ath79_uart_data[0].uartclk = clk_get_rate(clk);
		platform_device_register(&ath79_uart_device);
	} else if (soc_is_ar933x()) {
		ar933x_uart_data.uartclk = clk_get_rate(clk);
		platform_device_register(&ar933x_uart_device);
	} else {
		BUG();
	}
}

static struct platform_device ath79_wdt_device = {
	.name		= "ath79-wdt",
	.id		= -1,
};

void __init ath79_register_wdt(void)
{
	platform_device_register(&ath79_wdt_device);
}
