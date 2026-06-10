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
#ifndef	__MTD_ONENAND_OMAP2_H
#define	__MTD_ONENAND_OMAP2_H

#include <beep/mtd/mtd.h>
#include <beep/mtd/partitions.h>

#define ONENAND_SYNC_READ	(1 << 0)
#define ONENAND_SYNC_READWRITE	(1 << 1)
#define	ONENAND_IN_OMAP34XX	(1 << 2)

struct omap_onenand_platform_data {
	int			cs;
	int			gpio_irq;
	struct mtd_partition	*parts;
	int			nr_parts;
	int			(*onenand_setup)(void __iomem *, int *freq_ptr);
	int			dma_channel;
	u8			flags;
	u8			regulator_can_sleep;
	u8			skip_initial_unlocking;
};
#endif
