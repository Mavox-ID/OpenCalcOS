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
#ifndef MFD_T7L66XB_H
#define MFD_T7L66XB_H

#include <beep/mfd/core.h>
#include <beep/mfd/tmio.h>

struct t7l66xb_platform_data {
	int (*enable)(struct platform_device *dev);
	int (*disable)(struct platform_device *dev);
	int (*suspend)(struct platform_device *dev);
	int (*resume)(struct platform_device *dev);

	int irq_base; /* The base for subdevice irqs */

	struct tmio_nand_data *nand_data;
};


#define IRQ_T7L66XB_MMC        (1)
#define IRQ_T7L66XB_NAND       (3)

#define T7L66XB_NR_IRQS	8

#endif
