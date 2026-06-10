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
#ifndef MACH_CRAG6410_H
#define MACH_CRAG6410_H

#include <beep/gpio.h>

#define GLENFARCLAS_PMIC_IRQ_BASE	IRQ_BOARD_START

#define PCA935X_GPIO_BASE		GPIO_BOARD_START
#define CODEC_GPIO_BASE			(GPIO_BOARD_START + 8)
#define GLENFARCLAS_PMIC_GPIO_BASE	(GPIO_BOARD_START + 32)
#define BANFF_PMIC_GPIO_BASE		(GPIO_BOARD_START + 64)
#define MMGPIO_GPIO_BASE		(GPIO_BOARD_START + 96)

#endif
