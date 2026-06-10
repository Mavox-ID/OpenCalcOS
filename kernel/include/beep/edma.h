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
#ifndef __BEEP_EDMA_H
#define __BEEP_EDMA_H

struct dma_chan;

#if defined(CONFIG_TI_EDMA) || defined(CONFIG_TI_EDMA_MODULE)
bool edma_filter_fn(struct dma_chan *, void *);
#else
static inline bool edma_filter_fn(struct dma_chan *chan, void *param)
{
	return false;
}
#endif

#endif
