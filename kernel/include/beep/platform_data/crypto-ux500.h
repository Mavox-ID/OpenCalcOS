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
#ifndef _CRYPTO_UX500_H
#define _CRYPTO_UX500_H
#include <beep/dmaengine.h>
#include <beep/platform_data/dma-ste-dma40.h>

struct hash_platform_data {
	void *mem_to_engine;
	bool (*dma_filter)(struct dma_chan *chan, void *filter_param);
};

struct cryp_platform_data {
	struct stedma40_chan_cfg mem_to_engine;
	struct stedma40_chan_cfg engine_to_mem;
};

#endif
