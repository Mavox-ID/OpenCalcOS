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
#include <msp_regs.h>

static int __init msp_elb_setup(void)
{
#if defined(CONFIG_PMC_MSP7120_GW) \
 || defined(CONFIG_PMC_MSP7120_EVAL)
	/*
	 * Force all CNFG to be identical and equal to CS0,
	 * according to OPS doc
	 */
	*CS1_CNFG_REG = *CS2_CNFG_REG = *CS3_CNFG_REG = *CS0_CNFG_REG;
#endif
	return 0;
}

subsys_initcall(msp_elb_setup);
