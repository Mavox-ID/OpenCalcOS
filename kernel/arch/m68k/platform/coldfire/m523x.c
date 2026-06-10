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
 *	beep/arch/m68knommu/platform/523x/config.c
 *
 *	Sub-architcture dependent initialization code for the Freescale
 *	523x CPUs.
 *
 *	Copyright (C) 1999-2005, Greg Ungerer (gerg@snapgear.com)
 *	Copyright (C) 2001-2003, SnapGear Inc. (www.snapgear.com)
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
DEFINE_CLK(mcfpit0, "mcfpit.0", MCF_CLK);
DEFINE_CLK(mcfpit1, "mcfpit.1", MCF_CLK);
DEFINE_CLK(mcfpit2, "mcfpit.2", MCF_CLK);
DEFINE_CLK(mcfpit3, "mcfpit.3", MCF_CLK);
DEFINE_CLK(mcfuart0, "mcfuart.0", MCF_BUSCLK);
DEFINE_CLK(mcfuart1, "mcfuart.1", MCF_BUSCLK);
DEFINE_CLK(mcfuart2, "mcfuart.2", MCF_BUSCLK);
DEFINE_CLK(fec0, "fec.0", MCF_BUSCLK);

struct clk *mcf_clks[] = {
	&clk_pll,
	&clk_sys,
	&clk_mcfpit0,
	&clk_mcfpit1,
	&clk_mcfpit2,
	&clk_mcfpit3,
	&clk_mcfuart0,
	&clk_mcfuart1,
	&clk_mcfuart2,
	&clk_fec0,
	NULL
};

/***************************************************************************/

#if IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI)

static void __init m523x_qspi_init(void)
{
	u16 par;

	/* setup QSPS pins for QSPI with gpio CS control */
	writeb(0x1f, MCFGPIO_PAR_QSPI);
	/* and CS2 & CS3 as gpio */
	par = readw(MCFGPIO_PAR_TIMER);
	par &= 0x3f3f;
	writew(par, MCFGPIO_PAR_TIMER);
}

#endif /* IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI) */

/***************************************************************************/

static void __init m523x_fec_init(void)
{
	/* Set multi-function pins to ethernet use */
	writeb(readb(MCFGPIO_PAR_FECI2C) | 0xf0, MCFGPIO_PAR_FECI2C);
}

/***************************************************************************/

void __init config_BSP(char *commandp, int size)
{
	mach_sched_init = hw_timer_init;
	m523x_fec_init();
#if IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI)
	m523x_qspi_init();
#endif
}

/***************************************************************************/
