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

#define EXYNOS_UART_RESOURCE(_series, _nr)	\
static struct resource exynos##_series##_uart##_nr##_resource[] = {	\
	[0] = DEFINE_RES_MEM(EXYNOS##_series##_PA_UART##_nr, EXYNOS##_series##_SZ_UART),	\
	[1] = DEFINE_RES_IRQ(EXYNOS##_series##_IRQ_UART##_nr),	\
};

EXYNOS_UART_RESOURCE(4, 0)
EXYNOS_UART_RESOURCE(4, 1)
EXYNOS_UART_RESOURCE(4, 2)
EXYNOS_UART_RESOURCE(4, 3)

struct s3c24xx_uart_resources exynos4_uart_resources[] __initdata = {
	[0] = {
		.resources	= exynos4_uart0_resource,
		.nr_resources	= ARRAY_SIZE(exynos4_uart0_resource),
	},
	[1] = {
		.resources	= exynos4_uart1_resource,
		.nr_resources	= ARRAY_SIZE(exynos4_uart1_resource),
	},
	[2] = {
		.resources	= exynos4_uart2_resource,
		.nr_resources	= ARRAY_SIZE(exynos4_uart2_resource),
	},
	[3] = {
		.resources	= exynos4_uart3_resource,
		.nr_resources	= ARRAY_SIZE(exynos4_uart3_resource),
	},
};
