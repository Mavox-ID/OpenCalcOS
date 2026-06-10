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
#include <beep/types.h>
#include <beep/interrupt.h>
#include <beep/list.h>
#include <beep/platform_device.h>

#include <asm/mach/arch.h>
#include <asm/mach/irq.h>
#include <mach/hardware.h>
#include <mach/map.h>

#include <plat/devs.h>

/* Serial port registrations */

/* 64xx uarts are closer together */

static struct resource s3c64xx_uart0_resource[] = {
	[0] = DEFINE_RES_MEM(S3C_PA_UART0, SZ_256),
	[1] = DEFINE_RES_IRQ(IRQ_UART0),
};

static struct resource s3c64xx_uart1_resource[] = {
	[0] = DEFINE_RES_MEM(S3C_PA_UART1, SZ_256),
	[1] = DEFINE_RES_IRQ(IRQ_UART1),
};

static struct resource s3c6xx_uart2_resource[] = {
	[0] = DEFINE_RES_MEM(S3C_PA_UART2, SZ_256),
	[1] = DEFINE_RES_IRQ(IRQ_UART2),
};

static struct resource s3c64xx_uart3_resource[] = {
	[0] = DEFINE_RES_MEM(S3C_PA_UART3, SZ_256),
	[1] = DEFINE_RES_IRQ(IRQ_UART3),
};


struct s3c24xx_uart_resources s3c64xx_uart_resources[] __initdata = {
	[0] = {
		.resources	= s3c64xx_uart0_resource,
		.nr_resources	= ARRAY_SIZE(s3c64xx_uart0_resource),
	},
	[1] = {
		.resources	= s3c64xx_uart1_resource,
		.nr_resources	= ARRAY_SIZE(s3c64xx_uart1_resource),
	},
	[2] = {
		.resources	= s3c6xx_uart2_resource,
		.nr_resources	= ARRAY_SIZE(s3c6xx_uart2_resource),
	},
	[3] = {
		.resources	= s3c64xx_uart3_resource,
		.nr_resources	= ARRAY_SIZE(s3c64xx_uart3_resource),
	},
};
