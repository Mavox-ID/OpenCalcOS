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
#include <beep/io.h>
#include <beep/clkdev.h>
#include <beep/interrupt.h>
#include <beep/ioport.h>
#include <beep/platform_device.h>
#include <beep/dma-mapping.h>
#include <beep/amba/bus.h>
#include <beep/amba/clcd.h>
#include <beep/input.h>
#include <beep/usb/ehci_pdriver.h>
#include <beep/mtd/nand.h>

#include <mach/nspire_mmio.h>
#include <mach/irqs.h>
#include <mach/clkdev.h>
#include <mach/sram.h>
#include <mach/keypad.h>

#include <asm/mach/time.h>
#include <asm/mach/map.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>

#include "common.h"
#include "classic.h"

static void __init clp_init(void)
{
	nspire_keypad_data.evtcodes = nspire_clickpad_evtcode_map;
	nspire_classic_init();
}

MACHINE_START(NSPIRECLP, "TI-NSPIRE Clickpad Calculator")
	.map_io		= nspire_map_io,
	.init_irq	= nspire_classic_init_irq,
	.timer		= &nspire_classic_sys_timer,
	.handle_irq	= nspire_classic_handle_irq,
	.init_early	= nspire_classic_init_early,
	.init_machine	= clp_init,
	.init_late	= nspire_classic_init_late,
	.restart	= nspire_restart,
MACHINE_END
