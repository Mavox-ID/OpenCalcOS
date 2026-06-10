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
#include "gpiomux.h"

#if defined(CONFIG_MMC_MSM) || defined(CONFIG_MMC_MSM_MODULE)
	#define SDCC_DAT_0_3_CMD_ACTV_CFG (GPIOMUX_VALID | GPIOMUX_PULL_UP\
					| GPIOMUX_FUNC_1 | GPIOMUX_DRV_8MA)
	#define SDCC_CLK_ACTV_CFG (GPIOMUX_VALID | GPIOMUX_PULL_NONE\
					| GPIOMUX_FUNC_1 | GPIOMUX_DRV_8MA)
#else
	#define SDCC_DAT_0_3_CMD_ACTV_CFG 0
	#define SDCC_CLK_ACTV_CFG 0
#endif

#define SDC1_SUSPEND_CONFIG (GPIOMUX_VALID | GPIOMUX_PULL_DOWN\
				| GPIOMUX_FUNC_GPIO | GPIOMUX_DRV_2MA)

struct msm_gpiomux_config msm_gpiomux_configs[GPIOMUX_NGPIOS] = {
	[86] = { /* UART3 RX */
		.suspended = GPIOMUX_DRV_2MA | GPIOMUX_PULL_DOWN |
			     GPIOMUX_FUNC_1 | GPIOMUX_VALID,
	},
	[87] = { /* UART3 TX */
		.suspended = GPIOMUX_DRV_2MA | GPIOMUX_PULL_DOWN |
			     GPIOMUX_FUNC_1 | GPIOMUX_VALID,
	},
	/* SDC1 data[3:0] & CMD */
	[51 ... 55] = {
		.active = SDCC_DAT_0_3_CMD_ACTV_CFG,
		.suspended = SDC1_SUSPEND_CONFIG
	},
	/* SDC1 CLK */
	[56] = {
		.active = SDCC_CLK_ACTV_CFG,
		.suspended = SDC1_SUSPEND_CONFIG
	},
};
