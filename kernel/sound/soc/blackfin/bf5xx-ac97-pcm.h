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
#ifndef _BF5XX_AC97_PCM_H
#define _BF5XX_AC97_PCM_H

struct bf5xx_pcm_dma_params {
	char *name;			/* stream identifier */
};

struct bf5xx_gpio {
	u32 sys;
	u32 rx;
	u32 tx;
	u32 clk;
	u32 frm;
};

#endif
