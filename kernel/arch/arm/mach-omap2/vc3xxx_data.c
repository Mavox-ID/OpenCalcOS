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

#include "vc.h"

/*
 * VC data common to 34xx/36xx chips
 * XXX This stuff presumably belongs in the vc3xxx.c or vc.c file.
 */
static struct omap_vc_common omap3_vc_common = {
	.bypass_val_reg	 = OMAP3_PRM_VC_BYPASS_VAL_OFFSET,
	.data_shift	 = OMAP3430_DATA_SHIFT,
	.slaveaddr_shift = OMAP3430_SLAVEADDR_SHIFT,
	.regaddr_shift	 = OMAP3430_REGADDR_SHIFT,
	.valid		 = OMAP3430_VALID_MASK,
	.cmd_on_shift	 = OMAP3430_VC_CMD_ON_SHIFT,
	.cmd_on_mask	 = OMAP3430_VC_CMD_ON_MASK,
	.cmd_onlp_shift	 = OMAP3430_VC_CMD_ONLP_SHIFT,
	.cmd_ret_shift	 = OMAP3430_VC_CMD_RET_SHIFT,
	.cmd_off_shift	 = OMAP3430_VC_CMD_OFF_SHIFT,
	.i2c_cfg_hsen_mask = OMAP3430_HSEN_MASK,
	.i2c_cfg_reg	 = OMAP3_PRM_VC_I2C_CFG_OFFSET,
	.i2c_mcode_mask	 = OMAP3430_MCODE_MASK,
};

struct omap_vc_channel omap3_vc_mpu = {
	.flags = OMAP_VC_CHANNEL_DEFAULT,
	.common = &omap3_vc_common,
	.smps_sa_reg	 = OMAP3_PRM_VC_SMPS_SA_OFFSET,
	.smps_volra_reg	 = OMAP3_PRM_VC_SMPS_VOL_RA_OFFSET,
	.smps_cmdra_reg	 = OMAP3_PRM_VC_SMPS_CMD_RA_OFFSET,
	.cfg_channel_reg = OMAP3_PRM_VC_CH_CONF_OFFSET,
	.cmdval_reg = OMAP3_PRM_VC_CMD_VAL_0_OFFSET,
	.smps_sa_mask = OMAP3430_PRM_VC_SMPS_SA_SA0_MASK,
	.smps_volra_mask = OMAP3430_VOLRA0_MASK,
	.smps_cmdra_mask = OMAP3430_CMDRA0_MASK,
	.cfg_channel_sa_shift = OMAP3430_PRM_VC_SMPS_SA_SA0_SHIFT,
};

struct omap_vc_channel omap3_vc_core = {
	.common = &omap3_vc_common,
	.smps_sa_reg	 = OMAP3_PRM_VC_SMPS_SA_OFFSET,
	.smps_volra_reg	 = OMAP3_PRM_VC_SMPS_VOL_RA_OFFSET,
	.smps_cmdra_reg	 = OMAP3_PRM_VC_SMPS_CMD_RA_OFFSET,
	.cfg_channel_reg = OMAP3_PRM_VC_CH_CONF_OFFSET,
	.cmdval_reg = OMAP3_PRM_VC_CMD_VAL_1_OFFSET,
	.smps_sa_mask = OMAP3430_PRM_VC_SMPS_SA_SA1_MASK,
	.smps_volra_mask = OMAP3430_VOLRA1_MASK,
	.smps_cmdra_mask = OMAP3430_CMDRA1_MASK,
	.cfg_channel_sa_shift = OMAP3430_PRM_VC_SMPS_SA_SA1_SHIFT,
};

/*
 * Voltage levels for different operating modes: on, sleep, retention and off
 */
#define OMAP3_ON_VOLTAGE_UV		1200000
#define OMAP3_ONLP_VOLTAGE_UV		1000000
#define OMAP3_RET_VOLTAGE_UV		975000
#define OMAP3_OFF_VOLTAGE_UV		600000

struct omap_vc_param omap3_mpu_vc_data = {
	.on		= OMAP3_ON_VOLTAGE_UV,
	.onlp		= OMAP3_ONLP_VOLTAGE_UV,
	.ret		= OMAP3_RET_VOLTAGE_UV,
	.off		= OMAP3_OFF_VOLTAGE_UV,
};

struct omap_vc_param omap3_core_vc_data = {
	.on		= OMAP3_ON_VOLTAGE_UV,
	.onlp		= OMAP3_ONLP_VOLTAGE_UV,
	.ret		= OMAP3_RET_VOLTAGE_UV,
	.off		= OMAP3_OFF_VOLTAGE_UV,
};
