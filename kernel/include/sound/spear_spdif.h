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
#ifndef __SOUND_SPDIF_H
#define __SOUND_SPDIF_H

struct spear_spdif_platform_data {
	/* DMA params */
	void *dma_params;
	bool (*filter)(struct dma_chan *chan, void *slave);
	void (*reset_perip)(void);
};

#endif /* SOUND_SPDIF_H */
