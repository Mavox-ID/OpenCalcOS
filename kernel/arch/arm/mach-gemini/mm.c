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

#include <asm/mach/map.h>

#include <mach/hardware.h>

/* Page table mapping for I/O region */
static struct map_desc gemini_io_desc[] __initdata = {
	{
		.virtual	= IO_ADDRESS(GEMINI_GLOBAL_BASE),
		.pfn		=__phys_to_pfn(GEMINI_GLOBAL_BASE),
		.length		= SZ_512K,
		.type 		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(GEMINI_UART_BASE),
		.pfn		= __phys_to_pfn(GEMINI_UART_BASE),
		.length		= SZ_512K,
		.type 		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(GEMINI_TIMER_BASE),
		.pfn		= __phys_to_pfn(GEMINI_TIMER_BASE),
		.length		= SZ_512K,
		.type 		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(GEMINI_INTERRUPT_BASE),
		.pfn		= __phys_to_pfn(GEMINI_INTERRUPT_BASE),
		.length		= SZ_512K,
		.type 		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(GEMINI_POWER_CTRL_BASE),
		.pfn		= __phys_to_pfn(GEMINI_POWER_CTRL_BASE),
		.length		= SZ_512K,
		.type 		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(GEMINI_GPIO_BASE(0)),
		.pfn		= __phys_to_pfn(GEMINI_GPIO_BASE(0)),
		.length		= SZ_512K,
		.type 		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(GEMINI_GPIO_BASE(1)),
		.pfn		= __phys_to_pfn(GEMINI_GPIO_BASE(1)),
		.length		= SZ_512K,
		.type 		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(GEMINI_GPIO_BASE(2)),
		.pfn		= __phys_to_pfn(GEMINI_GPIO_BASE(2)),
		.length		= SZ_512K,
		.type 		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(GEMINI_FLASH_CTRL_BASE),
		.pfn		= __phys_to_pfn(GEMINI_FLASH_CTRL_BASE),
		.length		= SZ_512K,
		.type 		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(GEMINI_DRAM_CTRL_BASE),
		.pfn		= __phys_to_pfn(GEMINI_DRAM_CTRL_BASE),
		.length		= SZ_512K,
		.type 		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(GEMINI_GENERAL_DMA_BASE),
		.pfn		= __phys_to_pfn(GEMINI_GENERAL_DMA_BASE),
		.length		= SZ_512K,
		.type 		= MT_DEVICE,
	},
};

void __init gemini_map_io(void)
{
	iotable_init(gemini_io_desc, ARRAY_SIZE(gemini_io_desc));
}
