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
#ifndef _S6000_PCM_H
#define _S6000_PCM_H

struct snd_soc_dai;
struct snd_pcm_substream;

struct s6000_pcm_dma_params {
	unsigned int (*check_xrun)(struct snd_soc_dai *cpu_dai);
	int (*trigger)(struct snd_pcm_substream *substream, int cmd, int after);
	dma_addr_t sif_in;
	dma_addr_t sif_out;
	u32 dma_in;
	u32 dma_out;
	int irq;
	int same_rate;

	spinlock_t lock;
	int in_use;
	int rate;
};

#endif
