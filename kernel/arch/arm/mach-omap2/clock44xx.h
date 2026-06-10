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
#ifndef __ARCH_ARM_MACH_OMAP2_CLOCK44XX_H
#define __ARCH_ARM_MACH_OMAP2_CLOCK44XX_H

/*
 * OMAP4430_REGM4XEN_MULT: If the CM_CLKMODE_DPLL_ABE.DPLL_REGM4XEN bit is
 *    set, then the DPLL's lock frequency is multiplied by 4 (OMAP4430 TRM
 *    vV Section 3.6.3.3.1 "DPLLs Output Clocks Parameters")
 */
#define OMAP4430_REGM4XEN_MULT	4

int omap4xxx_clk_init(void);

#endif
