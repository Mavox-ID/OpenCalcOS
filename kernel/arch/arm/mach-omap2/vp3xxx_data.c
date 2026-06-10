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
#include <beep/err.h>
#include <beep/init.h>

#include "common.h"

#include "prm-regbits-34xx.h"
#include "voltage.h"

#include "vp.h"
#include "prm2xxx_3xxx.h"

static const struct omap_vp_ops omap3_vp_ops = {
	.check_txdone = omap3_prm_vp_check_txdone,
	.clear_txdone = omap3_prm_vp_clear_txdone,
};

/*
 * VP data common to 34xx/36xx chips
 * XXX This stuff presumably belongs in the vp3xxx.c or vp.c file.
 */
static const struct omap_vp_common omap3_vp_common = {
	.vpconfig_erroroffset_mask = OMAP3430_ERROROFFSET_MASK,
	.vpconfig_errorgain_mask = OMAP3430_ERRORGAIN_MASK,
	.vpconfig_initvoltage_mask = OMAP3430_INITVOLTAGE_MASK,
	.vpconfig_timeouten = OMAP3430_TIMEOUTEN_MASK,
	.vpconfig_initvdd = OMAP3430_INITVDD_MASK,
	.vpconfig_forceupdate = OMAP3430_FORCEUPDATE_MASK,
	.vpconfig_vpenable = OMAP3430_VPENABLE_MASK,
	.vstepmin_smpswaittimemin_shift = OMAP3430_SMPSWAITTIMEMIN_SHIFT,
	.vstepmax_smpswaittimemax_shift = OMAP3430_SMPSWAITTIMEMAX_SHIFT,
	.vstepmin_stepmin_shift = OMAP3430_VSTEPMIN_SHIFT,
	.vstepmax_stepmax_shift = OMAP3430_VSTEPMAX_SHIFT,
	.vlimitto_vddmin_shift = OMAP3430_VDDMIN_SHIFT,
	.vlimitto_vddmax_shift = OMAP3430_VDDMAX_SHIFT,
	.vlimitto_timeout_shift = OMAP3430_TIMEOUT_SHIFT,
	.vpvoltage_mask = OMAP3430_VPVOLTAGE_MASK,

	.ops = &omap3_vp_ops,
};

struct omap_vp_instance omap3_vp_mpu = {
	.id = OMAP3_VP_VDD_MPU_ID,
	.common = &omap3_vp_common,
	.vpconfig = OMAP3_PRM_VP1_CONFIG_OFFSET,
	.vstepmin = OMAP3_PRM_VP1_VSTEPMIN_OFFSET,
	.vstepmax = OMAP3_PRM_VP1_VSTEPMAX_OFFSET,
	.vlimitto = OMAP3_PRM_VP1_VLIMITTO_OFFSET,
	.vstatus = OMAP3_PRM_VP1_STATUS_OFFSET,
	.voltage = OMAP3_PRM_VP1_VOLTAGE_OFFSET,
};

struct omap_vp_instance omap3_vp_core = {
	.id = OMAP3_VP_VDD_CORE_ID,
	.common = &omap3_vp_common,
	.vpconfig = OMAP3_PRM_VP2_CONFIG_OFFSET,
	.vstepmin = OMAP3_PRM_VP2_VSTEPMIN_OFFSET,
	.vstepmax = OMAP3_PRM_VP2_VSTEPMAX_OFFSET,
	.vlimitto = OMAP3_PRM_VP2_VLIMITTO_OFFSET,
	.vstatus = OMAP3_PRM_VP2_STATUS_OFFSET,
	.voltage = OMAP3_PRM_VP2_VOLTAGE_OFFSET,
};

struct omap_vp_param omap3_mpu_vp_data = {
	.vddmin			= OMAP3430_VP1_VLIMITTO_VDDMIN,
	.vddmax			= OMAP3430_VP1_VLIMITTO_VDDMAX,
};

struct omap_vp_param omap3_core_vp_data = {
	.vddmin			= OMAP3430_VP2_VLIMITTO_VDDMIN,
	.vddmax			= OMAP3430_VP2_VLIMITTO_VDDMAX,
};
