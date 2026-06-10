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
#ifndef _IMX_PCM_H
#define _IMX_PCM_H

/*
 * Do not change this as the FIQ handler depends on this size
 */
#define IMX_SSI_DMABUF_SIZE	(64 * 1024)

struct imx_pcm_dma_params {
	int dma;
	unsigned long dma_addr;
	int burstsize;
	bool shared_peripheral;	/* The peripheral is on SPBA bus */
};

int snd_imx_pcm_mmap(struct snd_pcm_substream *substream,
		     struct vm_area_struct *vma);
int imx_pcm_new(struct snd_soc_pcm_runtime *rtd);
void imx_pcm_free(struct snd_pcm *pcm);

#endif /* _IMX_PCM_H */
