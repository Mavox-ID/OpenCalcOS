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
#undef DEBUG

#include <beep/kernel.h>
#include <beep/clk.h>
#include <beep/io.h>

#include "soc.h"
#include "iomap.h"
#include "clock.h"
#include "clock2xxx.h"
#include "cm2xxx.h"
#include "cm-regbits-24xx.h"

/**
 * omap2430_clk_i2chs_find_idlest - return CM_IDLEST info for 2430 I2CHS
 * @clk: struct clk * being enabled
 * @idlest_reg: void __iomem ** to store CM_IDLEST reg address into
 * @idlest_bit: pointer to a u8 to store the CM_IDLEST bit shift into
 * @idlest_val: pointer to a u8 to store the CM_IDLEST indicator
 *
 * OMAP2430 I2CHS CM_IDLEST bits are in CM_IDLEST1_CORE, but the
 * CM_*CLKEN bits are in CM_{I,F}CLKEN2_CORE.  This custom function
 * passes back the correct CM_IDLEST register address for I2CHS
 * modules.  No return value.
 */
static void omap2430_clk_i2chs_find_idlest(struct clk_hw_omap *clk,
					   void __iomem **idlest_reg,
					   u8 *idlest_bit,
					   u8 *idlest_val)
{
	*idlest_reg = OMAP2430_CM_REGADDR(CORE_MOD, CM_IDLEST);
	*idlest_bit = clk->enable_bit;
	*idlest_val = OMAP24XX_CM_IDLEST_VAL;
}

/* 2430 I2CHS has non-standard IDLEST register */
const struct clk_hw_omap_ops clkhwops_omap2430_i2chs_wait = {
	.find_idlest	= omap2430_clk_i2chs_find_idlest,
	.find_companion	= omap2_clk_dflt_find_companion,
};
