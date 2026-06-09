/*
 *	beep/arch/arm/mach-nspire/nspire_clp.c
 *
 *	Copyright (C) 2012 Daniel Tang <tangrs@tangrs.id.au>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2, as
 * published by the Free Software Foundation.
 *
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
