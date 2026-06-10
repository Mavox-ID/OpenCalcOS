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
#include <beep/io.h>
#include <asm/machdep.h>
#include <asm/coldfire.h>
#include <asm/mcfsim.h>

/*
 *	There are 2 common methods amongst the ColdFure parts for reseting
 *	the CPU. But there are couple of exceptions, the 5272 and the 547x
 *	have something completely special to them, and we let their specific
 *	subarch code handle them.
 */

#ifdef MCFSIM_SYPCR
static void mcf_cpu_reset(void)
{
	local_irq_disable();
	/* Set watchdog to soft reset, and enabled */
	__raw_writeb(0xc0, MCFSIM_SYPCR);
	for (;;)
		/* wait for watchdog to timeout */;
}
#endif

#ifdef MCF_RCR
static void mcf_cpu_reset(void)
{
	local_irq_disable();
	__raw_writeb(MCF_RCR_SWRESET, MCF_RCR);
}
#endif

static int __init mcf_setup_reset(void)
{
	mach_reset = mcf_cpu_reset;
	return 0;
}

arch_initcall(mcf_setup_reset);
