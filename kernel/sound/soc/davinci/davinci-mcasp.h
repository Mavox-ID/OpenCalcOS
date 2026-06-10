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
#ifndef DAVINCI_MCASP_H
#define DAVINCI_MCASP_H

#include <beep/io.h>
#include <beep/platform_data/davinci_asp.h>

#include "davinci-pcm.h"

#define DAVINCI_MCASP_RATES	SNDRV_PCM_RATE_8000_192000
#define DAVINCI_MCASP_I2S_DAI	0
#define DAVINCI_MCASP_DIT_DAI	1

struct davinci_audio_dev {
	struct davinci_pcm_dma_params dma_params[2];
	void __iomem *base;
	struct device *dev;

	/* McASP specific data */
	int	tdm_slots;
	u8	op_mode;
	u8	num_serializer;
	u8	*serial_dir;
	u8	version;
	u8	bclk_lrclk_ratio;

	/* McASP FIFO related */
	u8	txnumevt;
	u8	rxnumevt;
};

#endif	/* DAVINCI_MCASP_H */
