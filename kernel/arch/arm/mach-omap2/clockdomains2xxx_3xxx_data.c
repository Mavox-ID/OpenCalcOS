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
 * To-Do List
 * -> Port the Sleep/Wakeup dependencies for the domains
 *    from the Power domain framework
 */

#include <beep/kernel.h>
#include <beep/io.h>

#include "clockdomain.h"
#include "prm2xxx_3xxx.h"
#include "cm2xxx_3xxx.h"
#include "cm-regbits-24xx.h"
#include "cm-regbits-34xx.h"
#include "cm-regbits-44xx.h"
#include "prm-regbits-24xx.h"
#include "prm-regbits-34xx.h"

/*
 * Clockdomain dependencies for wkdeps/sleepdeps
 *
 * XXX Hardware dependencies (e.g., dependencies that cannot be
 * changed in software) are not included here yet, but should be.
 */

/* Wakeup dependency source arrays */

/* 2xxx-specific possible dependencies */

/* 2xxx PM_WKDEP_GFX: CORE, MPU, WKUP */
struct clkdm_dep gfx_24xx_wkdeps[] = {
	{ .clkdm_name = "core_l3_clkdm" },
	{ .clkdm_name = "core_l4_clkdm" },
	{ .clkdm_name = "mpu_clkdm" },
	{ .clkdm_name = "wkup_clkdm" },
	{ NULL },
};

/* 2xxx PM_WKDEP_DSP: CORE, MPU, WKUP */
struct clkdm_dep dsp_24xx_wkdeps[] = {
	{ .clkdm_name = "core_l3_clkdm" },
	{ .clkdm_name = "core_l4_clkdm" },
	{ .clkdm_name = "mpu_clkdm" },
	{ .clkdm_name = "wkup_clkdm" },
	{ NULL },
};


/*
 * OMAP2/3-common clockdomains
 *
 * Even though the 2420 has a single PRCM module from the
 * interconnect's perspective, internally it does appear to have
 * separate PRM and CM clockdomains.  The usual test case is
 * sys_clkout/sys_clkout2.
 */

/* This is an implicit clockdomain - it is never defined as such in TRM */
struct clockdomain wkup_common_clkdm = {
	.name		= "wkup_clkdm",
	.pwrdm		= { .name = "wkup_pwrdm" },
	.dep_bit	= OMAP_EN_WKUP_SHIFT,
	.flags		= CLKDM_ACTIVE_WITH_MPU,
};
