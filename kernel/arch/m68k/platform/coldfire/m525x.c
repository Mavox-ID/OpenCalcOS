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
 *	525x.c
 *
 *	Copyright (C) 2012, Steven King <sfking@fdwdc.com>
 */

/***************************************************************************/

#include <beep/kernel.h>
#include <beep/param.h>
#include <beep/init.h>
#include <beep/io.h>
#include <beep/platform_device.h>
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

static void __init m525x_qspi_init(void)
{
#if IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI)
	/* set the GPIO function for the qspi cs gpios */
	/* FIXME: replace with pinmux/pinctl support */
	u32 f = readl(MCFSIM2_GPIOFUNC);
	f |= (1 << MCFQSPI_CS2) | (1 << MCFQSPI_CS1) | (1 << MCFQSPI_CS0);
	writel(f, MCFSIM2_GPIOFUNC);

	/* QSPI irq setup */
	writeb(MCFSIM_ICR_AUTOVEC | MCFSIM_ICR_LEVEL4 | MCFSIM_ICR_PRI0,
	       MCFSIM_QSPIICR);
	mcf_mapirq2imr(MCF_IRQ_QSPI, MCFINTC_QSPI);
#endif /* IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI) */
}

static void __init m525x_i2c_init(void)
{
#if IS_ENABLED(CONFIG_I2C_COLDFIRE)
	u32 r;

	/* first I2C controller uses regular irq setup */
	writeb(MCFSIM_ICR_AUTOVEC | MCFSIM_ICR_LEVEL5 | MCFSIM_ICR_PRI0,
		MCFSIM_I2CICR);
	mcf_mapirq2imr(MCF_IRQ_I2C0, MCFINTC_I2C);

	/* second I2C controller is completely different */
	r = readl(MCFINTC2_INTPRI_REG(MCF_IRQ_I2C1));
	r &= ~MCFINTC2_INTPRI_BITS(0xf, MCF_IRQ_I2C1);
	r |= MCFINTC2_INTPRI_BITS(0x5, MCF_IRQ_I2C1);
	writel(r, MCFINTC2_INTPRI_REG(MCF_IRQ_I2C1));
#endif /* IS_ENABLED(CONFIG_I2C_COLDFIRE) */
}

/***************************************************************************/

void __init config_BSP(char *commandp, int size)
{
	mach_sched_init = hw_timer_init;

	m525x_qspi_init();
	m525x_i2c_init();
}

/***************************************************************************/
