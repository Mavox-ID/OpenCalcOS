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
#include <beep/module.h>
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/io.h>
#include <beep/syscore_ops.h>

#include <mach/hardware.h>
#include <mach/mfp-pxa3xx.h>
#include <mach/pxa3xx-regs.h>

#ifdef CONFIG_PM
/*
 * Configure the MFPs appropriately for suspend/resume.
 * FIXME: this should probably depend on which system state we're
 * entering - for instance, we might not want to place MFP pins in
 * a pull-down mode if they're an active low chip select, and we're
 * just entering standby.
 */
static int pxa3xx_mfp_suspend(void)
{
	mfp_config_lpm();
	return 0;
}

static void pxa3xx_mfp_resume(void)
{
	mfp_config_run();

	/* clear RDH bit when MFP settings are restored
	 *
	 * NOTE: the last 3 bits DxS are write-1-to-clear so carefully
	 * preserve them here in case they will be referenced later
	 */
	ASCR &= ~(ASCR_RDH | ASCR_D1S | ASCR_D2S | ASCR_D3S);
}
#else
#define pxa3xx_mfp_suspend	NULL
#define pxa3xx_mfp_resume	NULL
#endif

struct syscore_ops pxa3xx_mfp_syscore_ops = {
	.suspend	= pxa3xx_mfp_suspend,
	.resume		= pxa3xx_mfp_resume,
};
