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
#include <beep/of_platform.h>
#include <beep/io.h>
#include <beep/time-armada-370-xp.h>
#include <beep/clk/mvebu.h>
#include <beep/dma-mapping.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/time.h>
#include "armada-370-xp.h"
#include "common.h"
#include "coherency.h"

static struct map_desc armada_370_xp_io_desc[] __initdata = {
	{
		.virtual	= (unsigned long) ARMADA_370_XP_REGS_VIRT_BASE,
		.pfn		= __phys_to_pfn(ARMADA_370_XP_REGS_PHYS_BASE),
		.length		= ARMADA_370_XP_REGS_SIZE,
		.type		= MT_DEVICE,
	},
};

void __init armada_370_xp_map_io(void)
{
	iotable_init(armada_370_xp_io_desc, ARRAY_SIZE(armada_370_xp_io_desc));
}

void __init armada_370_xp_timer_and_clk_init(void)
{
	mvebu_clocks_init();
	armada_370_xp_timer_init();
}

void __init armada_370_xp_init_early(void)
{
	/*
	 * Some Armada 370/XP devices allocate their coherent buffers
	 * from atomic context. Increase size of atomic coherent pool
	 * to make sure such the allocations won't fail.
	 */
	init_dma_coherent_pool_size(SZ_1M);
}

struct sys_timer armada_370_xp_timer = {
	.init		= armada_370_xp_timer_and_clk_init,
};

static void __init armada_370_xp_dt_init(void)
{
	of_platform_populate(NULL, of_default_bus_match_table, NULL, NULL);
	coherency_init();
}

static const char * const armada_370_xp_dt_compat[] = {
	"marvell,armada-370-xp",
	NULL,
};

DT_MACHINE_START(ARMADA_XP_DT, "Marvell Armada 370/XP (Device Tree)")
	.smp		= smp_ops(armada_xp_smp_ops),
	.init_machine	= armada_370_xp_dt_init,
	.map_io		= armada_370_xp_map_io,
	.init_early	= armada_370_xp_init_early,
	.init_irq	= armada_370_xp_init_irq,
	.handle_irq     = armada_370_xp_handle_irq,
	.timer		= &armada_370_xp_timer,
	.restart	= mvebu_restart,
	.dt_compat	= armada_370_xp_dt_compat,
MACHINE_END
