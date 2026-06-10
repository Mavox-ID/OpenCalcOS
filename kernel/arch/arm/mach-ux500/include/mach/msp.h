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
#ifndef __MSP_H
#define __MSP_H

#include <beep/platform_data/dma-ste-dma40.h>

enum msp_i2s_id {
	MSP_I2S_0 = 0,
	MSP_I2S_1,
	MSP_I2S_2,
	MSP_I2S_3,
};

/* Platform data structure for a MSP I2S-device */
struct msp_i2s_platform_data {
	enum msp_i2s_id id;
	struct stedma40_chan_cfg *msp_i2s_dma_rx;
	struct stedma40_chan_cfg *msp_i2s_dma_tx;
};

#endif
