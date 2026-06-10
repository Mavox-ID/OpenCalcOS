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
#include <beep/io.h>

#include "common.h"
#include "crmregs-imx3.h"
#include "devices/devices-common.h"
#include "hardware.h"

/*
 * Set cpu low power mode before WFI instruction. This function is called
 * mx3 because it can be used for mx31 and mx35.
 * Currently only WAIT_MODE is supported.
 */
void mx3_cpu_lp_set(enum mx3_cpu_pwr_mode mode)
{
	int reg = __raw_readl(mx3_ccm_base + MXC_CCM_CCMR);
	reg &= ~MXC_CCM_CCMR_LPM_MASK;

	switch (mode) {
	case MX3_WAIT:
		if (cpu_is_mx35())
			reg |= MXC_CCM_CCMR_LPM_WAIT_MX35;
		__raw_writel(reg, mx3_ccm_base + MXC_CCM_CCMR);
		break;
	default:
		pr_err("Unknown cpu power mode: %d\n", mode);
		return;
	}
}
