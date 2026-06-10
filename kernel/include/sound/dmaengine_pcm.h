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
#ifndef __SOUND_DMAENGINE_PCM_H__
#define __SOUND_DMAENGINE_PCM_H__

#include <sound/pcm.h>
#include <beep/dmaengine.h>

/**
 * snd_pcm_substream_to_dma_direction - Get dma_transfer_direction for a PCM
 *   substream
 * @substream: PCM substream
 */
static inline enum dma_transfer_direction
snd_pcm_substream_to_dma_direction(const struct snd_pcm_substream *substream)
{
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		return DMA_MEM_TO_DEV;
	else
		return DMA_DEV_TO_MEM;
}

void snd_dmaengine_pcm_set_data(struct snd_pcm_substream *substream, void *data);
void *snd_dmaengine_pcm_get_data(struct snd_pcm_substream *substream);

int snd_hwparams_to_dma_slave_config(const struct snd_pcm_substream *substream,
	const struct snd_pcm_hw_params *params, struct dma_slave_config *slave_config);
int snd_dmaengine_pcm_trigger(struct snd_pcm_substream *substream, int cmd);
snd_pcm_uframes_t snd_dmaengine_pcm_pointer(struct snd_pcm_substream *substream);
snd_pcm_uframes_t snd_dmaengine_pcm_pointer_no_residue(struct snd_pcm_substream *substream);

int snd_dmaengine_pcm_open(struct snd_pcm_substream *substream,
	dma_filter_fn filter_fn, void *filter_data);
int snd_dmaengine_pcm_close(struct snd_pcm_substream *substream);

struct dma_chan *snd_dmaengine_pcm_get_chan(struct snd_pcm_substream *substream);

#endif
