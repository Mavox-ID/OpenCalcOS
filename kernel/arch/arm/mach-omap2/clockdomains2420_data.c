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

#include "soc.h"
#include "clockdomain.h"
#include "prm2xxx_3xxx.h"
#include "cm2xxx_3xxx.h"
#include "cm-regbits-24xx.h"
#include "prm-regbits-24xx.h"

/*
 * Clockdomain dependencies for wkdeps
 *
 * XXX Hardware dependencies (e.g., dependencies that cannot be
 * changed in software) are not included here yet, but should be.
 */

/* Wakeup dependency source arrays */

/* 2420-specific possible wakeup dependencies */

/* 2420 PM_WKDEP_MPU: CORE, DSP, WKUP */
static struct clkdm_dep mpu_2420_wkdeps[] = {
	{ .clkdm_name = "core_l3_clkdm" },
	{ .clkdm_name = "core_l4_clkdm" },
	{ .clkdm_name = "dsp_clkdm" },
	{ .clkdm_name = "wkup_clkdm" },
	{ NULL },
};

/* 2420 PM_WKDEP_CORE: DSP, GFX, MPU, WKUP */
static struct clkdm_dep core_2420_wkdeps[] = {
	{ .clkdm_name = "dsp_clkdm" },
	{ .clkdm_name = "gfx_clkdm" },
	{ .clkdm_name = "mpu_clkdm" },
	{ .clkdm_name = "wkup_clkdm" },
	{ NULL },
};

/*
 * 2420-only clockdomains
 */

static struct clockdomain mpu_2420_clkdm = {
	.name		= "mpu_clkdm",
	.pwrdm		= { .name = "mpu_pwrdm" },
	.flags		= CLKDM_CAN_HWSUP,
	.wkdep_srcs	= mpu_2420_wkdeps,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_MPU_MASK,
};

static struct clockdomain iva1_2420_clkdm = {
	.name		= "iva1_clkdm",
	.pwrdm		= { .name = "dsp_pwrdm" },
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.dep_bit	= OMAP24XX_PM_WKDEP_MPU_EN_DSP_SHIFT,
	.wkdep_srcs	= dsp_24xx_wkdeps,
	.clktrctrl_mask = OMAP2420_AUTOSTATE_IVA_MASK,
};

static struct clockdomain dsp_2420_clkdm = {
	.name		= "dsp_clkdm",
	.pwrdm		= { .name = "dsp_pwrdm" },
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_DSP_MASK,
};

static struct clockdomain gfx_2420_clkdm = {
	.name		= "gfx_clkdm",
	.pwrdm		= { .name = "gfx_pwrdm" },
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.wkdep_srcs	= gfx_24xx_wkdeps,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_GFX_MASK,
};

static struct clockdomain core_l3_2420_clkdm = {
	.name		= "core_l3_clkdm",
	.pwrdm		= { .name = "core_pwrdm" },
	.flags		= CLKDM_CAN_HWSUP,
	.wkdep_srcs	= core_2420_wkdeps,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_L3_MASK,
};

static struct clockdomain core_l4_2420_clkdm = {
	.name		= "core_l4_clkdm",
	.pwrdm		= { .name = "core_pwrdm" },
	.flags		= CLKDM_CAN_HWSUP,
	.wkdep_srcs	= core_2420_wkdeps,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_L4_MASK,
};

static struct clockdomain dss_2420_clkdm = {
	.name		= "dss_clkdm",
	.pwrdm		= { .name = "core_pwrdm" },
	.flags		= CLKDM_CAN_HWSUP,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_DSS_MASK,
};

static struct clockdomain *clockdomains_omap242x[] __initdata = {
	&wkup_common_clkdm,
	&mpu_2420_clkdm,
	&iva1_2420_clkdm,
	&dsp_2420_clkdm,
	&gfx_2420_clkdm,
	&core_l3_2420_clkdm,
	&core_l4_2420_clkdm,
	&dss_2420_clkdm,
	NULL,
};

void __init omap242x_clockdomains_init(void)
{
	if (!cpu_is_omap242x())
		return;

	clkdm_register_platform_funcs(&omap2_clkdm_operations);
	clkdm_register_clkdms(clockdomains_omap242x);
	clkdm_complete_init();
}
