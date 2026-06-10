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
#ifndef _AU1X_PCM_H
#define _AU1X_PCM_H

struct au1xpsc_audio_data {
	void __iomem *mmio;

	unsigned long cfg;
	unsigned long rate;

	struct snd_soc_dai_driver dai_drv;

	unsigned long pm[2];
	struct mutex lock;
	int dmaids[2];
};

/* easy access macros */
#define PSC_CTRL(x)	((unsigned long)((x)->mmio) + PSC_CTRL_OFFSET)
#define PSC_SEL(x)	((unsigned long)((x)->mmio) + PSC_SEL_OFFSET)
#define I2S_STAT(x)	((unsigned long)((x)->mmio) + PSC_I2SSTAT_OFFSET)
#define I2S_CFG(x)	((unsigned long)((x)->mmio) + PSC_I2SCFG_OFFSET)
#define I2S_PCR(x)	((unsigned long)((x)->mmio) + PSC_I2SPCR_OFFSET)
#define AC97_CFG(x)	((unsigned long)((x)->mmio) + PSC_AC97CFG_OFFSET)
#define AC97_CDC(x)	((unsigned long)((x)->mmio) + PSC_AC97CDC_OFFSET)
#define AC97_EVNT(x)	((unsigned long)((x)->mmio) + PSC_AC97EVNT_OFFSET)
#define AC97_PCR(x)	((unsigned long)((x)->mmio) + PSC_AC97PCR_OFFSET)
#define AC97_RST(x)	((unsigned long)((x)->mmio) + PSC_AC97RST_OFFSET)
#define AC97_STAT(x)	((unsigned long)((x)->mmio) + PSC_AC97STAT_OFFSET)

#endif
