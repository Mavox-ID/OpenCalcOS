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
#ifndef __BEEP_PCA9633_H
#define __BEEP_PCA9633_H
#include <beep/leds.h>

enum pca9633_outdrv {
	PCA9633_OPEN_DRAIN,
	PCA9633_TOTEM_POLE, /* aka push-pull */
};

struct pca9633_platform_data {
	struct led_platform_data leds;
	enum pca9633_outdrv outdrv;
};

#endif /* __BEEP_PCA9633_H*/
