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
#include <mach/dma.h>

struct pxa2xx_runtime_data {
	int dma_ch;
	struct pxa2xx_pcm_dma_params *params;
	pxa_dma_desc *dma_desc_array;
	dma_addr_t dma_desc_array_phys;
};

struct pxa2xx_pcm_client {
	struct pxa2xx_pcm_dma_params *playback_params;
	struct pxa2xx_pcm_dma_params *capture_params;
	int (*startup)(struct snd_pcm_substream *);
	void (*shutdown)(struct snd_pcm_substream *);
	int (*prepare)(struct snd_pcm_substream *);
};

extern int pxa2xx_pcm_new(struct snd_card *, struct pxa2xx_pcm_client *, struct snd_pcm **);

