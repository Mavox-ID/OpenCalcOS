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
#ifndef __INCLUDE_SOUND_ATMEL_ABDAC_H
#define __INCLUDE_SOUND_ATMEL_ABDAC_H

#include <beep/dw_dmac.h>

/**
 * struct atmel_abdac_pdata - board specific ABDAC configuration
 * @dws: DMA slave interface to use for sound playback.
 */
struct atmel_abdac_pdata {
	struct dw_dma_slave	dws;
};

#endif /* __INCLUDE_SOUND_ATMEL_ABDAC_H */
