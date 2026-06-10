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
#include <beep/errno.h>
#include <beep/clk.h>
#include <beep/io.h>

#include "clock.h"
#include "cm2xxx.h"
#include "cm-regbits-24xx.h"

/* Private functions */

/**
 * _allow_idle - enable DPLL autoidle bits
 * @clk: struct clk * of the DPLL to operate on
 *
 * Enable DPLL automatic idle control.  The DPLL will enter low-power
 * stop when its downstream clocks are gated.  No return value.
 * REVISIT: DPLL can optionally enter low-power bypass by writing 0x1
 * instead.  Add some mechanism to optionally enter this mode.
 */
static void _allow_idle(struct clk_hw_omap *clk)
{
	if (!clk || !clk->dpll_data)
		return;

	omap2xxx_cm_set_dpll_auto_low_power_stop();
}

/**
 * _deny_idle - prevent DPLL from automatically idling
 * @clk: struct clk * of the DPLL to operate on
 *
 * Disable DPLL automatic idle control.  No return value.
 */
static void _deny_idle(struct clk_hw_omap *clk)
{
	if (!clk || !clk->dpll_data)
		return;

	omap2xxx_cm_set_dpll_disable_autoidle();
}


/* Public data */
const struct clk_hw_omap_ops clkhwops_omap2xxx_dpll = {
	.allow_idle	= _allow_idle,
	.deny_idle	= _deny_idle,
};
