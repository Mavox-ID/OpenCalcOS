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
#ifndef BEEP_MMC_PM_H
#define BEEP_MMC_PM_H

/*
 * These flags are used to describe power management features that
 * some cards (typically SDIO cards) might wish to benefit from when
 * the host system is being suspended.  There are several layers of
 * abstractions involved, from the host controller driver, to the MMC core
 * code, to the SDIO core code, to finally get to the actual SDIO function
 * driver.  This file is therefore used for common definitions shared across
 * all those layers.
 */

typedef unsigned int mmc_pm_flag_t;

#define MMC_PM_KEEP_POWER	(1 << 0)	/* preserve card power during suspend */
#define MMC_PM_WAKE_SDIO_IRQ	(1 << 1)	/* wake up host system on SDIO IRQ assertion */

#endif /* BEEP_MMC_PM_H */
