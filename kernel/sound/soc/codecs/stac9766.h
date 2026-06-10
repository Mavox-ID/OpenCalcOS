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
#ifndef _STAC9766_H
#define _STAC9766_H

#define AC97_STAC_PAGE0 0x1000
#define AC97_STAC_DA_CONTROL (AC97_STAC_PAGE0 | 0x6A)
#define AC97_STAC_ANALOG_SPECIAL (AC97_STAC_PAGE0 | 0x6E)
#define AC97_STAC_STEREO_MIC 0x78

/* STAC9766 DAI ID's */
#define STAC9766_DAI_AC97_ANALOG		0
#define STAC9766_DAI_AC97_DIGITAL		1

#endif
