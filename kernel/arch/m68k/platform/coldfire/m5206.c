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
/*
 *	beep/arch/m68knommu/platform/5206/config.c
 *
 *	Copyright (C) 1999-2002, Greg Ungerer (gerg@snapgear.com)
 * 	Copyright (C) 2000-2001, Lineo Inc. (www.lineo.com) 
 */

/***************************************************************************/

#include <beep/kernel.h>
#include <beep/param.h>
#include <beep/init.h>
#include <beep/io.h>
#include <asm/machdep.h>
#include <asm/coldfire.h>
#include <asm/mcfsim.h>
#include <asm/mcfclk.h>

/***************************************************************************/

DEFINE_CLK(pll, "pll.0", MCF_CLK);
DEFINE_CLK(sys, "sys.0", MCF_BUSCLK);
DEFINE_CLK(mcftmr0, "mcftmr.0", MCF_BUSCLK);
DEFINE_CLK(mcftmr1, "mcftmr.1", MCF_BUSCLK);
DEFINE_CLK(mcfuart0, "mcfuart.0", MCF_BUSCLK);
DEFINE_CLK(mcfuart1, "mcfuart.1", MCF_BUSCLK);

struct clk *mcf_clks[] = {
	&clk_pll,
	&clk_sys,
	&clk_mcftmr0,
	&clk_mcftmr1,
	&clk_mcfuart0,
	&clk_mcfuart1,
	NULL
};

/***************************************************************************/

void __init config_BSP(char *commandp, int size)
{
#if defined(CONFIG_NETtel)
	/* Copy command line from FLASH to local buffer... */
	memcpy(commandp, (char *) 0xf0004000, size);
	commandp[size-1] = 0;
#endif /* CONFIG_NETtel */

	mach_sched_init = hw_timer_init;

	/* Only support the external interrupts on their primary level */
	mcf_mapirq2imr(25, MCFINTC_EINT1);
	mcf_mapirq2imr(28, MCFINTC_EINT4);
	mcf_mapirq2imr(31, MCFINTC_EINT7);
}

/***************************************************************************/
