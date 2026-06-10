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
#ifndef __BEEP_USB_S3C_HSOTG_H
#define __BEEP_USB_S3C_HSOTG_H

enum s3c_hsotg_dmamode {
	S3C_HSOTG_DMA_NONE,	/* do not use DMA at-all */
	S3C_HSOTG_DMA_ONLY,	/* always use DMA */
	S3C_HSOTG_DMA_DRV,	/* DMA is chosen by driver */
};

/**
 * struct s3c_hsotg_plat - platform data for high-speed otg/udc
 * @dma: Whether to use DMA or not.
 * @is_osc: The clock source is an oscillator, not a crystal
 */
struct s3c_hsotg_plat {
	enum s3c_hsotg_dmamode	dma;
	unsigned int		is_osc:1;
	int                     phy_type;

	int (*phy_init)(struct platform_device *pdev, int type);
	int (*phy_exit)(struct platform_device *pdev, int type);
};

extern void s3c_hsotg_set_platdata(struct s3c_hsotg_plat *pd);

#endif /* __BEEP_USB_S3C_HSOTG_H */
