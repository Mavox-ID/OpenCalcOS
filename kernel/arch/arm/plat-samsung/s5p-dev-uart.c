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
#include <beep/ioport.h>
#include <beep/platform_device.h>

#include <asm/mach/arch.h>
#include <asm/mach/irq.h>
#include <mach/hardware.h>
#include <mach/map.h>

#include <plat/devs.h>

 /* Serial port registrations */

static struct resource s5p_uart0_resource[] = {
	[0] = DEFINE_RES_MEM(S5P_PA_UART0, S5P_SZ_UART),
	[1] = DEFINE_RES_IRQ(IRQ_UART0),
};

static struct resource s5p_uart1_resource[] = {
	[0] = DEFINE_RES_MEM(S5P_PA_UART1, S5P_SZ_UART),
	[1] = DEFINE_RES_IRQ(IRQ_UART1),
};

static struct resource s5p_uart2_resource[] = {
	[0] = DEFINE_RES_MEM(S5P_PA_UART2, S5P_SZ_UART),
	[1] = DEFINE_RES_IRQ(IRQ_UART2),
};

static struct resource s5p_uart3_resource[] = {
#if CONFIG_SERIAL_SAMSUNG_UARTS > 3
	[0] = DEFINE_RES_MEM(S5P_PA_UART3, S5P_SZ_UART),
	[1] = DEFINE_RES_IRQ(IRQ_UART3),
#endif
};

static struct resource s5p_uart4_resource[] = {
#if CONFIG_SERIAL_SAMSUNG_UARTS > 4
	[0] = DEFINE_RES_MEM(S5P_PA_UART4, S5P_SZ_UART),
	[1] = DEFINE_RES_IRQ(IRQ_UART4),
#endif
};

static struct resource s5p_uart5_resource[] = {
#if CONFIG_SERIAL_SAMSUNG_UARTS > 5
	[0] = DEFINE_RES_MEM(S5P_PA_UART5, S5P_SZ_UART),
	[1] = DEFINE_RES_IRQ(IRQ_UART5),
#endif
};

struct s3c24xx_uart_resources s5p_uart_resources[] __initdata = {
	[0] = {
		.resources	= s5p_uart0_resource,
		.nr_resources	= ARRAY_SIZE(s5p_uart0_resource),
	},
	[1] = {
		.resources	= s5p_uart1_resource,
		.nr_resources	= ARRAY_SIZE(s5p_uart1_resource),
	},
	[2] = {
		.resources	= s5p_uart2_resource,
		.nr_resources	= ARRAY_SIZE(s5p_uart2_resource),
	},
	[3] = {
		.resources	= s5p_uart3_resource,
		.nr_resources	= ARRAY_SIZE(s5p_uart3_resource),
	},
	[4] = {
		.resources	= s5p_uart4_resource,
		.nr_resources	= ARRAY_SIZE(s5p_uart4_resource),
	},
	[5] = {
		.resources	= s5p_uart5_resource,
		.nr_resources	= ARRAY_SIZE(s5p_uart5_resource),
	},
};
