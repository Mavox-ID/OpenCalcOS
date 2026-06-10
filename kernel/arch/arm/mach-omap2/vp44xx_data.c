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

#include "prm44xx.h"
#include "prm-regbits-44xx.h"
#include "voltage.h"

#include "vp.h"

static const struct omap_vp_ops omap4_vp_ops = {
	.check_txdone = omap4_prm_vp_check_txdone,
	.clear_txdone = omap4_prm_vp_clear_txdone,
};

/*
 * VP data common to 44xx chips
 * XXX This stuff presumably belongs in the vp44xx.c or vp.c file.
 */
static const struct omap_vp_common omap4_vp_common = {
	.vpconfig_erroroffset_mask = OMAP4430_ERROROFFSET_MASK,
	.vpconfig_errorgain_mask = OMAP4430_ERRORGAIN_MASK,
	.vpconfig_initvoltage_mask = OMAP4430_INITVOLTAGE_MASK,
	.vpconfig_timeouten = OMAP4430_TIMEOUTEN_MASK,
	.vpconfig_initvdd = OMAP4430_INITVDD_MASK,
	.vpconfig_forceupdate = OMAP4430_FORCEUPDATE_MASK,
	.vpconfig_vpenable = OMAP4430_VPENABLE_MASK,
	.vstepmin_smpswaittimemin_shift = OMAP4430_SMPSWAITTIMEMIN_SHIFT,
	.vstepmax_smpswaittimemax_shift = OMAP4430_SMPSWAITTIMEMAX_SHIFT,
	.vstepmin_stepmin_shift = OMAP4430_VSTEPMIN_SHIFT,
	.vstepmax_stepmax_shift = OMAP4430_VSTEPMAX_SHIFT,
	.vlimitto_vddmin_shift = OMAP4430_VDDMIN_SHIFT,
	.vlimitto_vddmax_shift = OMAP4430_VDDMAX_SHIFT,
	.vlimitto_timeout_shift = OMAP4430_TIMEOUT_SHIFT,
	.vpvoltage_mask = OMAP4430_VPVOLTAGE_MASK,
	.ops = &omap4_vp_ops,
};

struct omap_vp_instance omap4_vp_mpu = {
	.id = OMAP4_VP_VDD_MPU_ID,
	.common = &omap4_vp_common,
	.vpconfig = OMAP4_PRM_VP_MPU_CONFIG_OFFSET,
	.vstepmin = OMAP4_PRM_VP_MPU_VSTEPMIN_OFFSET,
	.vstepmax = OMAP4_PRM_VP_MPU_VSTEPMAX_OFFSET,
	.vlimitto = OMAP4_PRM_VP_MPU_VLIMITTO_OFFSET,
	.vstatus = OMAP4_PRM_VP_MPU_STATUS_OFFSET,
	.voltage = OMAP4_PRM_VP_MPU_VOLTAGE_OFFSET,
};

struct omap_vp_instance omap4_vp_iva = {
	.id = OMAP4_VP_VDD_IVA_ID,
	.common = &omap4_vp_common,
	.vpconfig = OMAP4_PRM_VP_IVA_CONFIG_OFFSET,
	.vstepmin = OMAP4_PRM_VP_IVA_VSTEPMIN_OFFSET,
	.vstepmax = OMAP4_PRM_VP_IVA_VSTEPMAX_OFFSET,
	.vlimitto = OMAP4_PRM_VP_IVA_VLIMITTO_OFFSET,
	.vstatus = OMAP4_PRM_VP_IVA_STATUS_OFFSET,
	.voltage = OMAP4_PRM_VP_IVA_VOLTAGE_OFFSET,
};

struct omap_vp_instance omap4_vp_core = {
	.id = OMAP4_VP_VDD_CORE_ID,
	.common = &omap4_vp_common,
	.vpconfig = OMAP4_PRM_VP_CORE_CONFIG_OFFSET,
	.vstepmin = OMAP4_PRM_VP_CORE_VSTEPMIN_OFFSET,
	.vstepmax = OMAP4_PRM_VP_CORE_VSTEPMAX_OFFSET,
	.vlimitto = OMAP4_PRM_VP_CORE_VLIMITTO_OFFSET,
	.vstatus = OMAP4_PRM_VP_CORE_STATUS_OFFSET,
	.voltage = OMAP4_PRM_VP_CORE_VOLTAGE_OFFSET,
};

struct omap_vp_param omap4_mpu_vp_data = {
	.vddmin			= OMAP4_VP_MPU_VLIMITTO_VDDMIN,
	.vddmax			= OMAP4_VP_MPU_VLIMITTO_VDDMAX,
};

struct omap_vp_param omap4_iva_vp_data = {
	.vddmin			= OMAP4_VP_IVA_VLIMITTO_VDDMIN,
	.vddmax			= OMAP4_VP_IVA_VLIMITTO_VDDMAX,
};

struct omap_vp_param omap4_core_vp_data = {
	.vddmin			= OMAP4_VP_CORE_VLIMITTO_VDDMIN,
	.vddmax			= OMAP4_VP_CORE_VLIMITTO_VDDMAX,
};
