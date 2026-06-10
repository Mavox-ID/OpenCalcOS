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
#ifndef _PXA2XX_AC97_H
#define _PXA2XX_AC97_H

/* pxa2xx DAI ID's */
#define PXA2XX_DAI_AC97_HIFI	0
#define PXA2XX_DAI_AC97_AUX		1
#define PXA2XX_DAI_AC97_MIC		2

/* platform data */
extern struct snd_ac97_bus_ops pxa2xx_ac97_ops;

#endif
