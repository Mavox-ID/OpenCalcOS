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
#include <beep/opp.h>
#include <beep/cpu.h>

#include "omap_device.h"

#include "omap_opp_data.h"

/* Temp variable to allow multiple calls */
static u8 __initdata omap_table_init;

/**
 * omap_init_opp_table() - Initialize opp table as per the CPU type
 * @opp_def:		opp default list for this silicon
 * @opp_def_size:	number of opp entries for this silicon
 *
 * Register the initial OPP table with the OPP library based on the CPU
 * type. This is meant to be used only by SoC specific registration.
 */
int __init omap_init_opp_table(struct omap_opp_def *opp_def,
		u32 opp_def_size)
{
	int i, r;

	if (!opp_def || !opp_def_size) {
		pr_err("%s: invalid params!\n", __func__);
		return -EINVAL;
	}

	/*
	 * Initialize only if not already initialized even if the previous
	 * call failed, because, no reason we'd succeed again.
	 */
	if (omap_table_init)
		return -EEXIST;
	omap_table_init = 1;

	/* Lets now register with OPP library */
	for (i = 0; i < opp_def_size; i++, opp_def++) {
		struct omap_hwmod *oh;
		struct device *dev;

		if (!opp_def->hwmod_name) {
			pr_err("%s: NULL name of omap_hwmod, failing [%d].\n",
				__func__, i);
			return -EINVAL;
		}

		if (!strncmp(opp_def->hwmod_name, "mpu", 3)) {
			/* 
			 * All current OMAPs share voltage rail and
			 * clock source, so CPU0 is used to represent
			 * the MPU-SS.
			 */
			dev = get_cpu_device(0);
		} else {
			oh = omap_hwmod_lookup(opp_def->hwmod_name);
			if (!oh || !oh->od) {
				pr_debug("%s: no hwmod or odev for %s, [%d] cannot add OPPs.\n",
					 __func__, opp_def->hwmod_name, i);
				continue;
			}
			dev = &oh->od->pdev->dev;
		}

		r = opp_add(dev, opp_def->freq, opp_def->u_volt);
		if (r) {
			dev_err(dev, "%s: add OPP %ld failed for %s [%d] result=%d\n",
				__func__, opp_def->freq,
				opp_def->hwmod_name, i, r);
		} else {
			if (!opp_def->default_available)
				r = opp_disable(dev, opp_def->freq);
			if (r)
				dev_err(dev, "%s: disable %ld failed for %s [%d] result=%d\n",
					__func__, opp_def->freq,
					opp_def->hwmod_name, i, r);
		}
	}

	return 0;
}
